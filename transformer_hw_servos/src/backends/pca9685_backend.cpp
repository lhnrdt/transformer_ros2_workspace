// PCA9685 hardware PWM backend.
// Minimal register-level implementation using Linux i2c-dev interface.

#include "transformer_hw_servos/servo_backend.hpp"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <thread>

namespace transformer_hw_servos
{

  namespace
  {
    constexpr uint8_t REG_MODE1 = 0x00;
    constexpr uint8_t REG_MODE2 = 0x01;
    constexpr uint8_t REG_LED0_ON_L = 0x06;
    constexpr uint8_t REG_PRESCALE = 0xFE;

    bool write_reg(int fd, uint8_t reg, uint8_t val)
    {
      uint8_t buf[2]{reg, val};
      return (::write(fd, buf, 2) == 2);
    }

    bool read_reg(int fd, uint8_t reg, uint8_t &val)
    {
      if (::write(fd, &reg, 1) != 1)
        return false;
      if (::read(fd, &val, 1) != 1)
        return false;
      return true;
    }

    bool write_channel(int fd, int ch, uint16_t on_count, uint16_t off_count)
    {
      uint8_t base = REG_LED0_ON_L + 4 * ch;
      uint8_t buf[5];
      buf[0] = base;
      buf[1] = static_cast<uint8_t>(on_count & 0xFF);
      buf[2] = static_cast<uint8_t>((on_count >> 8) & 0x0F);
      buf[3] = static_cast<uint8_t>(off_count & 0xFF);
      buf[4] = static_cast<uint8_t>((off_count >> 8) & 0x0F);
      return (::write(fd, buf, 5) == 5);
    }
  } // namespace

  class Pca9685Backend : public IServoBackend
  {
  public:
    bool init(const ServoBackendConfig &cfg) override
    {
      cfg_ = cfg;
      fd_ = ::open(cfg_.i2c_bus.c_str(), O_RDWR);
      if (fd_ < 0)
        return false;
      if (ioctl(fd_, I2C_SLAVE, cfg_.pca9685_address) < 0)
        return false;

      // Reset MODE1 to a known state (restart bit cleared)
      write_reg(fd_, REG_MODE1, 0x00); // All call enabled by default
      std::this_thread::sleep_for(std::chrono::milliseconds(5));

      // Calculate prescale
      int freq = cfg_.freq_hz;
      if (freq < 24)
        freq = 24; // hardware limits approx 24..1526
      if (freq > 1526)
        freq = 1526;
      double prescale_val = 25000000.0 / (4096.0 * freq) - 1.0;
      int prescale = static_cast<int>(std::round(prescale_val));
      if (prescale < 3)
        prescale = 3;
      if (prescale > 255)
        prescale = 255;
      // Enter sleep before setting prescale
      uint8_t old_mode1 = 0;
      read_reg(fd_, REG_MODE1, old_mode1);
      uint8_t sleep_mode = (old_mode1 & 0x7F) | 0x10; // set SLEEP
      write_reg(fd_, REG_MODE1, sleep_mode);
      write_reg(fd_, REG_PRESCALE, static_cast<uint8_t>(prescale));
      // Wake up, enable auto-increment (AI) bit 5
      write_reg(fd_, REG_MODE1, (old_mode1 & 0xEF) | 0x20);
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
      // MODE2: totem pole (OUTDRV), non-inverted, change on STOP
      write_reg(fd_, REG_MODE2, 0x04);

      // Set initial pulses for requested logical channels (mapping applied in setPulse)
      for (int i = 0; i < cfg_.channels_in_use && i < 16; ++i)
      {
        setPulse(i, cfg_.initial_pulse_us[i]);
      }
      return true;
    }

    bool setPulse(int index, int pulse_us) override
    {
      if (fd_ < 0 || index < 0)
        return false;
      int hw_ch;
      if (index < 2)
      {
        hw_ch = cfg_.pca9685_channel[index];
      }
      else if (index < 6)
      {
        // Derive additional channel mapping: sequentially continue after the higher of the two configured channels
        int base = std::max(cfg_.pca9685_channel[0], cfg_.pca9685_channel[1]) + 1;
        hw_ch = base + (index - 2);
      }
      else
      {
        return false; // unsupported for now
      }
      if (hw_ch < 0 || hw_ch > 15)
        return false;
      // Convert microseconds to ticks
      double period_us = 1e6 / static_cast<double>(cfg_.freq_hz);
      if (period_us <= 0)
        return false;
      double ticks_per_us = 4096.0 / period_us;
      int offset_us = cfg_.offset_us[index];
      int on_count = static_cast<int>(std::fmod(offset_us * ticks_per_us, 4096.0));
      int pulse_ticks = static_cast<int>(pulse_us * ticks_per_us + 0.5);
      if (pulse_ticks < 0)
        pulse_ticks = 0;
      if (pulse_ticks > 4095)
        pulse_ticks = 4095; // saturate
      int off_count = (on_count + pulse_ticks) & 0x0FFF;
      return write_channel(fd_, hw_ch, static_cast<uint16_t>(on_count), static_cast<uint16_t>(off_count));
    }

    bool setDualPulse(int pulse0_us, int pulse1_us) override
    {
      bool ok0 = setPulse(0, pulse0_us);
      bool ok1 = setPulse(1, pulse1_us);
      return ok0 && ok1;
    }

    void shutdown() override
    {
      if (fd_ >= 0)
      {
        // Optionally set active channels to 0 width
        for (int i = 0; i < 2; ++i)
        {
          int ch = cfg_.pca9685_channel[i];
          if (ch >= 0 && ch < 16)
            write_channel(fd_, ch, 0, 0);
        }
        ::close(fd_);
        fd_ = -1;
      }
    }

    ~Pca9685Backend() override { shutdown(); }

  private:
    ServoBackendConfig cfg_;
    int fd_{-1};
  };

  std::unique_ptr<IServoBackend> create_pca9685_backend()
  {
    return std::make_unique<Pca9685Backend>();
  }

} // namespace transformer_hw_servos
