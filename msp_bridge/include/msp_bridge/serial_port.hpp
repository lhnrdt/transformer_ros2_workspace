#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <optional>

namespace msp_bridge {

class SerialPort {
public:
  SerialPort() = default;
  ~SerialPort();
  bool open(const std::string& device, int baudrate, int timeout_ms);
  void close();
  bool isOpen() const { return fd_ >= 0; }
  // Read up to max_len bytes, non-blocking; returns bytes read or -1 on error
  int readSome(uint8_t* buf, size_t max_len);
  // Write all bytes; returns true on success
  bool writeAll(const uint8_t* data, size_t len);
private:
  int fd_{-1};
};

} // namespace msp_bridge
