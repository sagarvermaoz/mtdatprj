/*
 * MtData application driving the whole program
*/
#include "application.hpp"
#include "json_helper.hpp"
#include <thread>
#include <iostream>
#include "serial_interface.hpp"
#include <cstring>
#include <unistd.h>

namespace mtdata_prj {
void Run(const char *com_port) {

// start the MtDataAppThread thread and pass it the serial parameters
std::thread thread(MtDataAppThread,com_port);
thread.detach();

while(true){
  // once we start here, ideally we should never return
}

}

void MtDataAppThread(const char* com_port){
  // serial interface object
  auto serial_interface = new serial_interface::SerialInterface(com_port, 9600);
  // json helper object
  auto json_helper = new json_helper::JsonHelper();

  // open serial
  if (!serial_interface->Open()) {
    std::cout<<"serial interface open error, exit..."<<std::endl;
    exit(0);
  }
  // configure the handle and initialize
  serial_interface->Initialize();

  char read_buffer[200];
  int bytes_read = 0;
  while (true) {
    // read serial data
   bytes_read = serial_interface->Read(read_buffer, 200); // Read
    sleep(1);
    json_helper->GetJsonFormattedOutput(read_buffer);
    std::memset(read_buffer,0,200);
  }
}

} // namespace mtdata_prj
