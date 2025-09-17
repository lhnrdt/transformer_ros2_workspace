#include "transformer_hw_actuators/actuator_node.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <algorithm>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

namespace transformer_hw_actuators
{

    ActuatorNode::ActuatorNode(const rclcpp::NodeOptions &options)
        : Node("actuator_node", options)
    {
        // Parameters with DC motor defaults
        pwmchip_index_ = this->declare_parameter<int>("pwmchip_index", 0);
        gpiochip_name_ = this->declare_parameter<std::string>("gpiochip_name", "gpiochip4");

        // NOTE: integer arrays are int64 in ROS 2 parameters. Declare as int64 and cast.
        auto pwm_channels_i64 = this->declare_parameter<std::vector<int64_t>>("pwm_channels", {1, 0});
        auto dir_gpios_i64 = this->declare_parameter<std::vector<int64_t>>("dir_gpios", {19, 5});

        pwm_channels_.assign(pwm_channels_i64.begin(), pwm_channels_i64.end());
        dir_gpios_.assign(dir_gpios_i64.begin(), dir_gpios_i64.end());

        dir_active_high_ = this->declare_parameter<std::vector<bool>>("dir_active_high", {true, true});
        period_ns_ = this->declare_parameter<int64_t>("period_ns", 50'000); // 20 kHz
        initial_percent_ = this->declare_parameter<int>("initial_percent", 0);
    brake_on_zero_ = this->declare_parameter<bool>("brake_on_zero", false);
    feedback_period_ms_ = this->declare_parameter<int>("feedback_period_ms", 50); // 20 Hz feedback

        if (pwm_channels_.size() != dir_gpios_.size())
        {
            RCLCPP_FATAL(get_logger(), "pwm_channels and dir_gpios must have same size");
            throw std::runtime_error("parameter size mismatch");
        }

        chip_path_ = "/sys/class/pwm/pwmchip" + std::to_string(pwmchip_index_);

        // open chosen chip
        gpio_chip_ = gpiod_chip_open_by_name(gpiochip_name_.c_str());
        if (!gpio_chip_)
        {
            RCLCPP_FATAL(get_logger(), "Failed to open %s (permission or wrong chip?)",
                         gpiochip_name_.c_str());
            throw std::runtime_error("gpiod open failed");
        }
        dir_lines_.resize(dir_gpios_.size(), nullptr);
        for (size_t i = 0; i < dir_gpios_.size(); ++i)
        {
            dir_lines_[i] = gpiod_chip_get_line(gpio_chip_, dir_gpios_[i]);
            if (!dir_lines_[i])
            {
                RCLCPP_FATAL(get_logger(), "Failed to get GPIO line %d", dir_gpios_[i]);
                throw std::runtime_error("gpiod get line failed");
            }
            int rv = gpiod_line_request_output(dir_lines_[i], "transformer_hw_actuators", 0);
            if (rv < 0)
            {
                RCLCPP_FATAL(get_logger(), "Failed to request output for GPIO %d (permission?)", dir_gpios_[i]);
                throw std::runtime_error("gpiod request failed");
            }
        }

        // Initialize each PWM channel
        for (int ch : pwm_channels_)
        {
            std::string err;
            if (!exportChannel(ch, err))
            {
                RCLCPP_ERROR(get_logger(), "Failed exporting PWM channel %d: %s", ch, err.c_str());
            }
            if (!ensurePeriod(ch, err))
            {
                RCLCPP_ERROR(get_logger(), "Failed setting period for channel %d: %s", ch, err.c_str());
            }
            if (!setDutyPercent(ch, std::abs(initial_percent_), err))
            {
                RCLCPP_ERROR(get_logger(), "Failed setting initial duty for channel %d: %s", ch, err.c_str());
            }
            if (!enableChannel(ch, true, err))
            {
                RCLCPP_ERROR(get_logger(), "Failed enabling channel %d: %s", ch, err.c_str());
            }
        }
        // Set initial directions
        for (size_t i = 0; i < dir_lines_.size(); ++i)
        {
            std::string err;
            bool fwd = initial_percent_ >= 0;
            if (!setDirection(i, fwd, err))
            {
                RCLCPP_ERROR(get_logger(), "Failed to set initial direction for actuator %zu: %s", i, err.c_str());
            }
        }

        // Create action server
        action_server_ = rclcpp_action::create_server<MoveActuator>(
            this,
            "move_actuator",
            std::bind(&ActuatorNode::handleGoal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&ActuatorNode::handleCancel, this, std::placeholders::_1),
            std::bind(&ActuatorNode::handleAccepted, this, std::placeholders::_1));

        RCLCPP_INFO(get_logger(), "ActuatorNode ready for DC motors: pwmchip=%d period=%ldns", pwmchip_index_, (long)period_ns_);
    }

    ActuatorNode::~ActuatorNode()
    {
        for (auto *line : dir_lines_)
        {
            if (line)
                gpiod_line_release(line);
        }
        if (gpio_chip_)
            gpiod_chip_close(gpio_chip_);
    }

    // ===== Filesystem helpers =====

    bool ActuatorNode::pathExists(const std::string &path)
    {
        std::error_code ec;
        return fs::exists(path, ec);
    }

    bool ActuatorNode::writeFile(const std::string &path, const std::string &value, std::string &err)
    {
        std::ofstream f(path);
        if (!f.is_open())
        {
            err = "open failed";
            return false;
        }
        f << value;
        if (!f)
        {
            err = "write failed";
            return false;
        }
        return true;
    }

    std::string ActuatorNode::chPath(int channel, const std::string &leaf) const
    {
        std::ostringstream ss;
        ss << "/pwm" << channel << "/" << leaf;
        return ss.str();
    }

    bool ActuatorNode::exportChannel(int channel, std::string &err)
    {
        auto pwm_path = chip_path_ + "/pwm" + std::to_string(channel);
        if (!pathExists(pwm_path))
        {
            auto export_path = chip_path_ + "/export";
            if (!writeFile(export_path, std::to_string(channel), err))
                return false;
            rclcpp::sleep_for(50ms);
        }
        return true;
    }

    bool ActuatorNode::ensurePeriod(int channel, std::string &err)
    {
        auto period_path = chip_path_ + chPath(channel, "period");
        return writeFile(period_path, std::to_string(period_ns_), err);
    }

    bool ActuatorNode::enableChannel(int channel, bool enable, std::string &err)
    {
        auto enable_path = chip_path_ + chPath(channel, "enable");
        return writeFile(enable_path, enable ? "1" : "0", err);
    }

    bool ActuatorNode::setDutyPercent(int channel, int percent, std::string &err)
    {
        if (percent < 0)
            percent = 0;
        if (percent > 100)
            percent = 100;
        int64_t duty_ns = (period_ns_ * static_cast<int64_t>(percent)) / 100;
        auto duty_path = chip_path_ + chPath(channel, "duty_cycle");
        return writeFile(duty_path, std::to_string(duty_ns), err);
    }

    bool ActuatorNode::setDirection(size_t actuator_idx, bool forward, std::string &err)
    {
        if (actuator_idx >= dir_lines_.size())
        {
            err = "bad actuator index";
            return false;
        }
        bool active_high = dir_active_high_.at(actuator_idx);
        int level = forward ? 1 : 0;
        if (!active_high)
            level = level ? 0 : 1;
        int rv = gpiod_line_set_value(dir_lines_[actuator_idx], level);
        if (rv < 0)
        {
            err = std::string("gpiod_line_set_value failed: ") + std::strerror(errno);
            return false;
        }
        return true;
    }

    // ===== Action callbacks =====

    rclcpp_action::GoalResponse ActuatorNode::handleGoal(
        const rclcpp_action::GoalUUID & /*uuid*/,
        std::shared_ptr<const MoveActuator::Goal> goal)
    {
        auto now = std::chrono::steady_clock::now();
        auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        RCLCPP_INFO(get_logger(), "[T%lld] handleGoal: actuator=%d speed_percent=%d duration_ms=%d",
                    static_cast<long long>(now_ms), goal->actuator, goal->speed_percent, goal->duration_ms);
        if (goal->actuator < 0 || goal->actuator >= static_cast<int>(pwm_channels_.size()))
        {
            RCLCPP_WARN(get_logger(), "Rejecting goal: invalid actuator %d", goal->actuator);
            return rclcpp_action::GoalResponse::REJECT;
        }
        if (goal->speed_percent < -100 || goal->speed_percent > 100)
        {
            RCLCPP_WARN(get_logger(), "Clamping speed_percent %d to [-100,100]", goal->speed_percent);
        }
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse ActuatorNode::handleCancel(
        const std::shared_ptr<GoalHandleMove> /*goal_handle*/)
    {
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void ActuatorNode::handleAccepted(const std::shared_ptr<GoalHandleMove> goal_handle)
    {
        auto now = std::chrono::steady_clock::now();
        auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        RCLCPP_INFO(get_logger(), "[T%lld] handleAccepted: spinning up execute thread", static_cast<long long>(now_ms));
        std::thread{std::bind(&ActuatorNode::execute, this, goal_handle)}.detach();
    }

    void ActuatorNode::execute(const std::shared_ptr<GoalHandleMove> goal_handle)
    {
        auto t_exec_start = std::chrono::steady_clock::now();
        auto t_exec_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_exec_start.time_since_epoch()).count();
        RCLCPP_INFO(get_logger(), "[T%lld] execute: begin", static_cast<long long>(t_exec_ms));

        const auto goal = goal_handle->get_goal();
        auto result = std::make_shared<MoveActuator::Result>();
        auto feedback = std::make_shared<MoveActuator::Feedback>();

        int idx = goal->actuator;
        int channel = pwm_channels_.at(idx);
        int spd = std::clamp(goal->speed_percent, -100, 100);
        int duration_ms = goal->duration_ms;

        std::string err;
        auto t_before_dir = std::chrono::steady_clock::now();
        if (!setDirection(idx, spd >= 0, err))
        {
            result->success = false;
            result->message = std::string("setDirection failed: ") + err;
            goal_handle->abort(result);
            return;
        }
        auto t_after_dir = std::chrono::steady_clock::now();
        auto t_before_duty = std::chrono::steady_clock::now();
        if (!setDutyPercent(channel, std::abs(spd), err))
        {
            result->success = false;
            result->message = std::string("setDutyPercent failed: ") + err;
            goal_handle->abort(result);
            return;
        }
        auto t_after_duty = std::chrono::steady_clock::now();

        auto dt_dir = std::chrono::duration_cast<std::chrono::microseconds>(t_after_dir - t_before_dir).count();
        auto dt_duty = std::chrono::duration_cast<std::chrono::microseconds>(t_after_duty - t_before_duty).count();
        RCLCPP_INFO(get_logger(), "execute: setDirection=%0.3f ms, setDutyPercent=%0.3f ms",
                    dt_dir / 1000.0, dt_duty / 1000.0);

        // If no duration requested, publish one feedback and finish immediately
        if (duration_ms <= 0)
        {
            feedback->current_speed_percent = spd;
            feedback->elapsed_ms = 0;
            feedback->remaining_ms = 0;
            goal_handle->publish_feedback(feedback);

            result->success = true;
            result->message = "Speed set (no timing)";
            auto t_done = std::chrono::steady_clock::now();
            auto dt_total = std::chrono::duration_cast<std::chrono::milliseconds>(t_done - t_exec_start).count();
            RCLCPP_INFO(get_logger(), "execute: completed (no timing) in %lld ms", static_cast<long long>(dt_total));
            goal_handle->succeed(result);
            return;
        }

        // Timed execution loop
        auto start = std::chrono::steady_clock::now();
        int elapsed_ms = 0;
    const int period_ms = std::max(1, feedback_period_ms_);
    rclcpp::Rate rate(1000ms / period_ms);

        while (rclcpp::ok())
        {
            // Check cancel
            if (goal_handle->is_canceling())
            {
                // Stop the motor
                (void)setDutyPercent(channel, 0, err);
                feedback->current_speed_percent = 0;
                auto now = std::chrono::steady_clock::now();
                elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count());
                feedback->elapsed_ms = elapsed_ms;
                feedback->remaining_ms = std::max(0, duration_ms - elapsed_ms);
                goal_handle->publish_feedback(feedback);

                auto cancel_result = std::make_shared<MoveActuator::Result>();
                cancel_result->success = false;
                cancel_result->message = "Canceled";
                goal_handle->canceled(cancel_result);
                RCLCPP_INFO(get_logger(), "Goal canceled");
                return;
            }

            auto now = std::chrono::steady_clock::now();
            elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count());
            if (elapsed_ms >= duration_ms)
                break;

            // Publish feedback
            feedback->current_speed_percent = spd;
            feedback->elapsed_ms = elapsed_ms;
            feedback->remaining_ms = std::max(0, duration_ms - elapsed_ms);
            goal_handle->publish_feedback(feedback);

            rate.sleep();
        }

        // Stop the motor at the end of the duration
        (void)setDutyPercent(channel, 0, err);
        feedback->current_speed_percent = 0;
        feedback->elapsed_ms = duration_ms;
        feedback->remaining_ms = 0;
        goal_handle->publish_feedback(feedback);

        result->success = true;
        result->message = "Completed duration";
        auto t_done = std::chrono::steady_clock::now();
        auto dt_total = std::chrono::duration_cast<std::chrono::milliseconds>(t_done - t_exec_start).count();
        RCLCPP_INFO(get_logger(), "execute: completed in %lld ms (requested %d ms)", static_cast<long long>(dt_total), duration_ms);
        goal_handle->succeed(result);
    }

} // namespace transformer_hw_actuators

// ---- main ----
#include <rclcpp/rclcpp.hpp>
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<transformer_hw_actuators::ActuatorNode>();
    rclcpp::executors::MultiThreadedExecutor exec;
    exec.add_node(node);
    exec.spin();
    rclcpp::shutdown();
    return 0;
}