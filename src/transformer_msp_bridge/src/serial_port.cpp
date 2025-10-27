// Implements the lightweight POSIX serial wrapper used by the MSP bridge.
#include "transformer_msp_bridge/serial_port.hpp"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cerrno>
#include <cstring>

namespace transformer_msp_bridge
{

  namespace
  {
    int baudToFlag(int baud)
    {
      switch (baud)
      {
      case 9600:
        return B9600;
      case 19200:
        return B19200;
      case 38400:
        return B38400;
      case 57600:
        return B57600;
      case 115200:
        return B115200;
      case 230400:
        return B230400;
      case 460800:
        return B460800;
      case 921600:
        return B921600;
      default:
        return B115200;
      }
    }
  }

  SerialPort::~SerialPort() { close(); }

  bool SerialPort::open(const std::string &device, int baudrate, int timeout_ms)
  {
    close();
    fd_ = ::open(device.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_ < 0)
      return false;
    termios tio{};
    if (tcgetattr(fd_, &tio) != 0)
    {
      close();
      return false;
    }
    cfmakeraw(&tio);
    int baudflag = baudToFlag(baudrate);
    cfsetispeed(&tio, baudflag);
    cfsetospeed(&tio, baudflag);
    tio.c_cflag |= (CLOCAL | CREAD);
    // VMIN/VTIME for blocking read; we keep non-blocking so set minimal
    tio.c_cc[VMIN] = 0;                 // return immediately
    tio.c_cc[VTIME] = timeout_ms / 100; // deciseconds
    if (tcsetattr(fd_, TCSANOW, &tio) != 0)
    {
      close();
      return false;
    }
    return true;
  }

  void SerialPort::close()
  {
    if (fd_ >= 0)
    {
      ::close(fd_);
      fd_ = -1;
    }
  }

  int SerialPort::readSome(uint8_t *buf, size_t max_len)
  {
    if (fd_ < 0)
      return -1;
    int n = ::read(fd_, buf, max_len);
    if (n < 0)
    {
      if (errno == EAGAIN || errno == EWOULDBLOCK)
        return 0; // non-blocking no data
      return -1;
    }
    return n;
  }

  bool SerialPort::writeAll(const uint8_t *data, size_t len)
  {
    if (fd_ < 0)
      return false;
    size_t off = 0;
    while (off < len)
    {
      int n = ::write(fd_, data + off, len - off);
      if (n < 0)
      {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
          continue;
        }
        return false;
      }
      off += static_cast<size_t>(n);
    }
    return true;
  }

} // namespace transformer_msp_bridge
