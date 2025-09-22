// Clean lgpio-only implementation controlling two servos via lgTxServo

#include <rclcpp/rclcpp.hpp>
#include <lgpio.h>

#include <atomic>
#include <string>
#include <algorithm>
#include <pthread.h>
#include <sched.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/resource.h>

// Generated headers
#include "transformer_hw_servos/srv/set_servo_pulse.hpp"
#include "transformer_hw_servos/srv/set_dual_servo_pulse.hpp"

class DualServoNode : public rclcpp::Node
{
public:
    using SetServoPulse = transformer_hw_servos::srv::SetServoPulse;
    using SetDualServoPulse = transformer_hw_servos::srv::SetDualServoPulse;

    DualServoNode()
        : Node("transformer_hw_servos"),
          gpiochip_name_(this->declare_parameter<std::string>("gpiochip_name", "gpiochip4")),
          gpio_servo0_(this->declare_parameter<int>("gpio_servo0", 6)),  // GPIO6
          gpio_servo1_(this->declare_parameter<int>("gpio_servo1", 18)), // GPIO18
          period_us_(this->declare_parameter<int>("period_us", 20000))   // 50 Hz
    {
        // Optional RT and CPU affinity tuning to reduce jitter
        use_realtime_ = this->declare_parameter<bool>("use_realtime", false);
        rt_priority_ = this->declare_parameter<int>("rt_priority", 80);
        lock_memory_ = this->declare_parameter<bool>("lock_memory", true);
        cpu_affinity_ = this->declare_parameter<int>("cpu_affinity", -1); // -1 disabled
        // Optional pre-fault buffer to reduce page faults under memory pressure
        prefault_mb_ = this->declare_parameter<int>("prefault_mb", 0);
        setup_realtime();

        // Limits and initial values
        min_us_global_ = this->declare_parameter<int>("min_us", 1350);
        max_us_global_ = this->declare_parameter<int>("max_us", 2500);
        min_us_servo_[0] = this->declare_parameter<int>("min_us_servo0", min_us_global_);
        min_us_servo_[1] = this->declare_parameter<int>("min_us_servo1", min_us_global_);
        max_us_servo_[0] = this->declare_parameter<int>("max_us_servo0", max_us_global_);
        max_us_servo_[1] = this->declare_parameter<int>("max_us_servo1", max_us_global_);
        // Per-servo start offset in microseconds (0..period)
        servo_offset_us_[0] = this->declare_parameter<int>("servo_offset_servo0_us", 0);
        servo_offset_us_[1] = this->declare_parameter<int>("servo_offset_servo1_us", 0);
        // Number of pulses to send (0=infinite)
        servo_cycles_ = this->declare_parameter<int>("servo_cycles", 0);
        // lgpio's lgTxServo supports ~[500, 2500] us. Clamp config to backend limits and warn.
        const int kBackendMinUs = 500;
        const int kBackendMaxUs = 2500;
        auto clamp_to_backend = [&](int &mn, int &mx, const char *label){
            int old_mn = mn, old_mx = mx;
            if (mn < kBackendMinUs) mn = kBackendMinUs;
            if (mx > kBackendMaxUs) mx = kBackendMaxUs;
            if (mn != old_mn || mx != old_mx)
            {
                RCLCPP_WARN(get_logger(),
                    "%s limits adjusted to backend range [%d,%d] (was [%d,%d])",
                    label, kBackendMinUs, kBackendMaxUs, old_mn, old_mx);
            }
        };
        clamp_to_backend(min_us_global_, max_us_global_, "global");
        clamp_to_backend(min_us_servo_[0], max_us_servo_[0], "servo0");
        clamp_to_backend(min_us_servo_[1], max_us_servo_[1], "servo1");
        int initial_us = this->declare_parameter<int>("initial_us", 1500);
        int initial_us_servo0 = this->declare_parameter<int>("initial_us_servo0", initial_us);
        int initial_us_servo1 = this->declare_parameter<int>("initial_us_servo1", initial_us);
        pulse_us_[0].store(clampPulse(0, initial_us_servo0));
        pulse_us_[1].store(clampPulse(1, initial_us_servo1));

    RCLCPP_INFO(get_logger(),
            "Params: gpiochip=%s, servos=(%d,%d), period_us=%d, freq_hz=%d",
            gpiochip_name_.c_str(), gpio_servo0_, gpio_servo1_, period_us_,
            period_us_ > 0 ? (int)(1000000 / period_us_) : 50);
    RCLCPP_INFO(get_logger(),
            "Limits: global=[%d,%d], servo0=[%d,%d], servo1=[%d,%d]",
            min_us_global_, max_us_global_, min_us_servo_[0], max_us_servo_[0],
            min_us_servo_[1], max_us_servo_[1]);
    RCLCPP_INFO(get_logger(),
            "Initial: servo0=%d(us)->%d(us), servo1=%d(us)->%d(us)",
            initial_us_servo0, pulse_us_[0].load(), initial_us_servo1, pulse_us_[1].load());

        // Open chip and claim outputs via lgpio
        int chip_index = parseChipIndex(gpiochip_name_);
        lg_handle_ = lgGpiochipOpen(chip_index);
        if (lg_handle_ < 0)
        {
            RCLCPP_FATAL(get_logger(), "lgpio: Failed to open %s", gpiochip_name_.c_str());
            throw std::runtime_error("lgpio open failed");
        }
        if (lgGpioClaimOutput(lg_handle_, 0, gpio_servo0_, 0) < 0 ||
            lgGpioClaimOutput(lg_handle_, 0, gpio_servo1_, 0) < 0)
        {
            lgGpiochipClose(lg_handle_);
            lg_handle_ = -1;
            throw std::runtime_error("lgpio: Failed to claim GPIO as outputs");
        }

        // Compute frequency from period and clamp to lgTxServo range [40, 500] Hz
        freq_hz_ = (period_us_ > 0) ? static_cast<int>(1000000 / period_us_) : 50;
        int orig_freq = freq_hz_;
        if (freq_hz_ < 40) { freq_hz_ = 40; }
        if (freq_hz_ > 500) { freq_hz_ = 500; }
        if (freq_hz_ != orig_freq)
        {
            RCLCPP_WARN(get_logger(), "Requested period %dus implies %d Hz; clamped to %d Hz per lgTxServo",
                        period_us_, orig_freq, freq_hz_);
        }
        // Clamp/normalize offsets against the effective period derived from frequency
        int effective_period_us = 1000000 / std::max(1, freq_hz_);
        for (int i = 0; i < 2; ++i)
        {
            int old = servo_offset_us_[i];
            if (servo_offset_us_[i] < 0) servo_offset_us_[i] = 0;
            if (effective_period_us > 0)
            {
                // keep within [0, effective_period_us)
                if (servo_offset_us_[i] >= effective_period_us)
                {
                    servo_offset_us_[i] = servo_offset_us_[i] % effective_period_us;
                }
            }
            if (servo_offset_us_[i] != old)
            {
                RCLCPP_WARN(get_logger(), "servo%d offset adjusted to %dus within [0,%d)", i, servo_offset_us_[i], effective_period_us);
            }
        }
        if (servo_cycles_ < 0)
        {
            RCLCPP_WARN(get_logger(), "servo_cycles was negative; setting to 0 (infinite)");
            servo_cycles_ = 0;
        }

    // Start servo pulses at initial positions (with configured offset and cycles)
    lgTxServo(lg_handle_, gpio_servo0_, pulse_us_[0].load(), freq_hz_, servo_offset_us_[0], servo_cycles_);
    lgTxServo(lg_handle_, gpio_servo1_, pulse_us_[1].load(), freq_hz_, servo_offset_us_[1], servo_cycles_);

        // Services for setting pulse widths
        srv_single_ = this->create_service<SetServoPulse>(
            "set_servo_pulse",
            std::bind(&DualServoNode::handleSetPulse, this,
                      std::placeholders::_1, std::placeholders::_2));

        srv_dual_ = this->create_service<SetDualServoPulse>(
            "set_dual_servo_pulse",
            std::bind(&DualServoNode::handleSetDualPulse, this,
                      std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(get_logger(), "Servos ready on GPIO%d and GPIO%d via lgpio (%s) @ %d Hz; offsets=(%dus,%dus), cycles=%d",
            gpio_servo0_, gpio_servo1_, gpiochip_name_.c_str(), freq_hz_,
            servo_offset_us_[0], servo_offset_us_[1], servo_cycles_);
    }

    ~DualServoNode() override
    {
        // Stop servo pulses (set width 0) then close
        if (lg_handle_ >= 0)
        {
            lgTxServo(lg_handle_, gpio_servo0_, 0, freq_hz_, 0, 0);
            lgTxServo(lg_handle_, gpio_servo1_, 0, freq_hz_, 0, 0);
            lgGpiochipClose(lg_handle_);
            lg_handle_ = -1;
        }
    }

private:
    void setup_realtime()
    {
        if (!use_realtime_)
            return;
        // Lock memory to avoid page faults
        if (lock_memory_)
        {
            // Try to raise memlock soft limit to hard limit
            struct rlimit rlim;
            if (getrlimit(RLIMIT_MEMLOCK, &rlim) == 0)
            {
                struct rlimit newlim = rlim;
                newlim.rlim_cur = rlim.rlim_max; // raise soft to hard
                if (setrlimit(RLIMIT_MEMLOCK, &newlim) != 0)
                {
                    RCLCPP_WARN(get_logger(), "setrlimit MEMLOCK failed: %m");
                }
            }

            if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0)
            {
                RCLCPP_WARN(get_logger(), "mlockall failed: %m");
            }
            // Pre-fault a small buffer if requested
            if (prefault_mb_ > 0)
            {
                size_t bytes = static_cast<size_t>(prefault_mb_) * 1024ULL * 1024ULL;
                try
                {
                    prefault_buffer_.resize(bytes, 0);
                    // Touch each page
                    size_t page = static_cast<size_t>(sysconf(_SC_PAGESIZE));
                    for (size_t i = 0; i < bytes; i += page)
                    {
                        prefault_buffer_[i] = static_cast<uint8_t>(i);
                    }
                }
                catch (const std::exception &e)
                {
                    RCLCPP_WARN(get_logger(), "prefault allocation failed: %s", e.what());
                }
            }
        }

        // Set SCHED_FIFO priority
        struct sched_param sp;
        sp.sched_priority = std::max(1, std::min(99, rt_priority_));
        int rc = pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);
        if (rc != 0)
        {
            RCLCPP_WARN(get_logger(), "pthread_setschedparam failed (are you root/cap_sys_nice?): %d", rc);
        }

        // Set CPU affinity if requested
        if (cpu_affinity_ >= 0)
        {
            cpu_set_t set;
            CPU_ZERO(&set);
            int cpu = cpu_affinity_ % std::max(1L, sysconf(_SC_NPROCESSORS_ONLN));
            CPU_SET(cpu, &set);
            rc = pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
            if (rc != 0)
            {
                RCLCPP_WARN(get_logger(), "pthread_setaffinity_np failed: %d", rc);
            }
            else
            {
                RCLCPP_INFO(get_logger(), "Bound node thread to CPU %d with SCHED_FIFO prio %d", cpu, sp.sched_priority);
            }
        }
    }

    void handleSetPulse(const SetServoPulse::Request::SharedPtr req,
                        SetServoPulse::Response::SharedPtr res)
    {
        int idx = req->servo_index;
        if (idx < 0 || idx > 1)
        {
            res->success = false;
            res->message = "servo_index must be 0 or 1";
            return;
        }
        int us = clampPulse(idx, req->pulse_us);
        pulse_us_[idx].store(us);
        // Update servo pulse via lgpio
        int gpio = (idx == 0) ? gpio_servo0_ : gpio_servo1_;
        if (lg_handle_ >= 0)
            lgTxServo(lg_handle_, gpio, us, freq_hz_, servo_offset_us_[idx], servo_cycles_);
        res->success = true;
        res->message = "updated";
    }

    void handleSetDualPulse(const SetDualServoPulse::Request::SharedPtr req,
                            SetDualServoPulse::Response::SharedPtr res)
    {
        int us0 = clampPulse(0, req->pulse_us0);
        int us1 = clampPulse(1, req->pulse_us1);
        pulse_us_[0].store(us0);
        pulse_us_[1].store(us1);
        if (lg_handle_ >= 0)
        {
            // Back-to-back updates to keep them as close in time as possible
            lgTxServo(lg_handle_, gpio_servo0_, us0, freq_hz_, servo_offset_us_[0], servo_cycles_);
            lgTxServo(lg_handle_, gpio_servo1_, us1, freq_hz_, servo_offset_us_[1], servo_cycles_);
        }
        res->success = true;
        res->message = "updated both";
    }

    static int parseChipIndex(const std::string &name)
    {
        // Expect formats like "gpiochip4" -> 4; fallback to 0
        int idx = 0;
        size_t pos = name.find_last_not_of("0123456789");
        if (pos != std::string::npos && pos + 1 < name.size())
        {
            try
            {
                idx = std::stoi(name.substr(pos + 1));
            }
            catch (...)
            {
                idx = 0;
            }
        }
        return idx;
    }

    int clampPulse(int idx, int us) const
    {
        int mn = min_us_servo_[idx];
        int mx = max_us_servo_[idx];
        if (mn > mx)
            std::swap(mn, mx);
        if (us < mn)
            return mn;
        if (us > mx)
            return mx;
        return us;
    }

private:
    std::string gpiochip_name_;
    int gpio_servo0_;
    int gpio_servo1_;
    int period_us_;
    int freq_hz_{50};
    int min_us_global_;
    int max_us_global_;
    int min_us_servo_[2];
    int max_us_servo_[2];
    std::atomic<int> pulse_us_[2];
    int servo_offset_us_[2]{0,0};
    int servo_cycles_{0};
    int lg_handle_{-1};

    rclcpp::Service<SetServoPulse>::SharedPtr srv_single_;
    rclcpp::Service<SetDualServoPulse>::SharedPtr srv_dual_;

    // RT tuning
    bool use_realtime_{false};
    int rt_priority_{80};
    bool lock_memory_{true};
    int cpu_affinity_{-1};
    int prefault_mb_{0};
    std::vector<uint8_t> prefault_buffer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    try
    {
        auto node = std::make_shared<DualServoNode>();
        rclcpp::spin(node);
    }
    catch (const std::exception &e)
    {
        RCLCPP_FATAL(rclcpp::get_logger("transformer_hw_servos"), "Fatal: %s", e.what());
    }
    rclcpp::shutdown();
    return 0;
}
