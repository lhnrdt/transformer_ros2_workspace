// Lgpio backend implementation adapted from the original node logic.

#include "transformer_hw_servos/servo_backend.hpp"

#include <lgpio.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>
#include <algorithm>
#include <atomic>
#include <cstring>
#include <stdexcept>

namespace transformer_hw_servos
{

  class LgpioServoBackend : public IServoBackend
  {
  public:
    bool init(const ServoBackendConfig &cfg) override
    {
      cfg_ = cfg;
      apply_realtime();
      // Parse chip index from trailing digits of name
      int chip_index = 0;
      {
        auto &name = cfg_.gpiochip_name;
        size_t pos = name.find_last_not_of("0123456789");
        if (pos != std::string::npos && pos + 1 < name.size())
        {
          try
          {
            chip_index = std::stoi(name.substr(pos + 1));
          }
          catch (...)
          {
            chip_index = 0;
          }
        }
      }
      handle_ = lgGpiochipOpen(chip_index);
      if (handle_ < 0)
        return false;
      if (lgGpioClaimOutput(handle_, 0, cfg_.gpio_servo[0], 0) < 0 ||
          lgGpioClaimOutput(handle_, 0, cfg_.gpio_servo[1], 0) < 0)
      {
        lgGpiochipClose(handle_);
        handle_ = -1;
        return false;
      }
      // Start initial pulses (only first two physical GPIOs supported)
      lgTxServo(handle_, cfg_.gpio_servo[0], cfg_.initial_pulse_us[0], cfg_.freq_hz, cfg_.offset_us[0], cfg_.cycles);
      if (cfg_.channels_in_use > 1)
        lgTxServo(handle_, cfg_.gpio_servo[1], cfg_.initial_pulse_us[1], cfg_.freq_hz, cfg_.offset_us[1], cfg_.cycles);
      return true;
    }

    bool setPulse(int index, int pulse_us) override
    {
      if (handle_ < 0 || index < 0 || index > 1)
        return false;
      lgTxServo(handle_, cfg_.gpio_servo[index], pulse_us, cfg_.freq_hz, cfg_.offset_us[index], cfg_.cycles);
      return true;
    }

    bool setDualPulse(int pulse0_us, int pulse1_us) override
    {
      if (handle_ < 0)
        return false;
      lgTxServo(handle_, cfg_.gpio_servo[0], pulse0_us, cfg_.freq_hz, cfg_.offset_us[0], cfg_.cycles);
      lgTxServo(handle_, cfg_.gpio_servo[1], pulse1_us, cfg_.freq_hz, cfg_.offset_us[1], cfg_.cycles);
      return true;
    }

    void shutdown() override
    {
      if (handle_ >= 0)
      {
        // Stop outputs
        lgTxServo(handle_, cfg_.gpio_servo[0], 0, cfg_.freq_hz, 0, 0);
        lgTxServo(handle_, cfg_.gpio_servo[1], 0, cfg_.freq_hz, 0, 0);
        lgGpiochipClose(handle_);
        handle_ = -1;
      }
    }

    ~LgpioServoBackend() override { shutdown(); }

  private:
    void apply_realtime()
    {
      if (!cfg_.use_realtime)
        return;
      if (cfg_.lock_memory)
      {
        struct rlimit rlim;
        if (getrlimit(RLIMIT_MEMLOCK, &rlim) == 0)
        {
          struct rlimit nl = rlim;
          nl.rlim_cur = rlim.rlim_max;
          setrlimit(RLIMIT_MEMLOCK, &nl);
        }
        mlockall(MCL_CURRENT | MCL_FUTURE);
        if (cfg_.prefault_mb > 0)
        {
          size_t bytes = static_cast<size_t>(cfg_.prefault_mb) * 1024ULL * 1024ULL;
          prefault_buffer_.assign(bytes, 0);
          size_t page = static_cast<size_t>(sysconf(_SC_PAGESIZE));
          for (size_t i = 0; i < bytes; i += page)
            prefault_buffer_[i] = static_cast<uint8_t>(i);
        }
      }
      struct sched_param sp;
      sp.sched_priority = std::max(1, std::min(99, cfg_.rt_priority));
      pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);
      if (cfg_.cpu_affinity >= 0)
      {
        cpu_set_t set;
        CPU_ZERO(&set);
        int cpu = cfg_.cpu_affinity % std::max(1L, sysconf(_SC_NPROCESSORS_ONLN));
        CPU_SET(cpu, &set);
        pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
      }
    }
    ServoBackendConfig cfg_;
    int handle_{-1};
    std::vector<uint8_t> prefault_buffer_;
  };

  std::unique_ptr<IServoBackend> create_lgpio_backend()
  {
    return std::make_unique<LgpioServoBackend>();
  }

} // namespace transformer_hw_servos
