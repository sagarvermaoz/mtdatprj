/*
 * Interface file source code for accessing serial port hardware peripheral
*/

#include "serial_interface.hpp"
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

namespace mtdata_prj {
namespace serial_interface {
/*
* Ctor
*/
SerialInterface::SerialInterface(const char *com_port, int baudrate)
    : baudrate_{baudrate} {

  std::strncpy(com_port_, com_port, std::strlen(com_port));
}

void SerialInterface::Initialize() {
  // get current struct attributes
  tcgetattr(serial_handle_, &serial_port_settings_);
  cfsetispeed(&serial_port_settings_, baudrate_); // Baud rate: 9600
  // 8N1 Mode
  serial_port_settings_.c_cflag &= ~PARENB;  // No Parity
  serial_port_settings_.c_cflag &= ~CSTOPB;  // 1 Stop bit
  serial_port_settings_.c_cflag |= CS8;      // bits = 8
  serial_port_settings_.c_cflag &= ~CRTSCTS; //  Hardware flow Control = None
  serial_port_settings_.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable XON/XOFF

  // Set the termios struct
  if ((tcsetattr(serial_handle_, TCSANOW, &serial_port_settings_)) == 0) {
    std::cout << "SerialInterface::Initialize[OK]" << std::endl;
    tcflush(serial_handle_, TCIFLUSH); // flush
  } else {
    std::cout << "SerialInterface::Initialize[FAIL]" << std::endl;
    return;
  }
}

void SerialInterface::DeInitialize() {
  std::cout << "SerialInterface::DeInitialize[OK]:Dummy" << std::endl;
}

bool SerialInterface::Open() {
  // Read only mode
  auto ret{false};
  serial_handle_ = open(com_port_, O_RDONLY);
  if (serial_handle_ == -1) {
    std::cout << "SerialInterface::Open[FAIL]" << std::endl;
  } else {
    std::cout << "SerialInterface::Open[OK]" << std::endl;
    ret = true;
  }
  return ret;
}

int SerialInterface::Read(char *read_buffer, int read_size) {
  return read(serial_handle_, read_buffer, read_size);
}

void SerialInterface::Close() {
  auto ret = close(serial_handle_);
  if(ret != -1){
  std::cout << "SerialInterface::Close[OK]" << std::endl;
  }else{
  std::cout << "SerialInterface::Close[FAIL]" << std::endl;
  }
}

} // namespace serial_interface
} // namespace mtdata_prj
