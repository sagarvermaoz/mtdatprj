/*
 * MtData application driving the whole program
 */
#include "application.hpp"
#include "json_helper.hpp"
#include "serial_interface.hpp"
#include <cstring>
#include <iostream>
#include <thread>
#include <unistd.h>

namespace mtdata_prj {

void Application::Run(const char *com_port) {
  std::cout << "Run MtData application" << std::endl;
  // start the MtDataAppThread thread and pass it the serial parameters
  // std::thread mtdata_thread(MtDataAppThread, com_port);
  // mtdata_thread.detach();

  // serial interface object
  auto serial_interface = new serial_interface::SerialInterface(com_port, 9600);

  // json helper object
  auto json_helper = new json_helper::JsonHelper();

  // open serial
  if (!serial_interface->Open()) {
    std::cout << "serial interface open error, exit..." << std::endl;
    exit(0);
  }

  // configure the handle and initialize
  serial_interface->Initialize();

  int delay_time_in_sec{10};
  char read_buffer[2048];
  int bytes_read = 0;

  while (true) {
    // flush before read
    serial_interface->Flush();
    // read latest serial data
    bytes_read = serial_interface->Read(read_buffer, 2048); // Read
    // just call the below method to get formatted output
    json_helper->GetJsonFormattedOutput(read_buffer, bytes_read);
    std::memset(read_buffer, 0, 2048);
    sleep(delay_time_in_sec);
  }
}

} // namespace mtdata_prj
