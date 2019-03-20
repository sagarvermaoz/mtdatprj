/*
 * Interface file class header for accessing serial port hardware peripheral
*/

#pragma once

#include "serial_interface_base.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

namespace mtdata_prj {
namespace serial_interface {

class SerialInterface : public SerialInterfaceBase {
public:
  /**
   * Constructor to create instance of serial peripheral
   * @param const char* Serial Comm port
   * @param int baudrate
   */
  explicit SerialInterface(const char *com_port, int baudrate);

  /** @brief Initialize the serial peripheral
   *  @return none
   */
  void Initialize();

  /** @brief DeInitialize the serial peripheral
   *  @param none
   *  @return none
   */
  void DeInitialize();

  /** @brief Read the serial peripheral
   *  @param char *read_buffer, int read_size
   *  @return int num of read bytes
   */
  int Read(char *read_buffer, int read_size);

  /** @brief Open the serial peripheral
   *  @param none
   *  @return bool
   */
  bool Open();

  /** @brief Close the serial peripheral
   *  @param none
   *  @return none
   */
  void Close();

private:
  int baudrate_;
  char com_port_[10];
  int serial_handle_;

  // Set Attributes of serial port using termios struct
  struct termios serial_port_settings_;
};

} // namespace serial_interface
} // namespace mtdata_prj
