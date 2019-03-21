/*
 * Interface file base class header for accessing serial port hardware
 * peripheral
 */

#pragma once

namespace mtdata_prj {
namespace serial_interface {

/**
 * @class SerialInterfaceBase
 * Serial interface base class
 */
class SerialInterfaceBase {
public:
  /** @brief Initialize the serial
   *  @param none
   *  @return none
   */
  virtual void Initialize() = 0;

  /** @brief DeInitialize the serial
   *  @param none
   *  @return none
   */
  virtual void DeInitialize() = 0;

  /** @brief Read the serial
   *  @param char *read_buffer, int read_size
   *  @return int num of read bytes
   */
  virtual int Read(char *read_buffer, int read_size) = 0;

  /** @brief Open the serial
   *  @param none
   *  @return bool
   */
  virtual bool Open() = 0;

  /** @brief Close the serial
   *  @param none
   *  @return none
   */
  virtual void Close() = 0;

  /** @brief Flush the serial peripheral
   *  @param none
   *  @return none
   */
  virtual void Flush() = 0;
};

} // namespace serial_interface
} // namespace mtdata_prj
