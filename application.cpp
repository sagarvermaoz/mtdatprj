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
  std::thread mtdata_thread(MtDataAppThread, com_port);
  mtdata_thread.detach();
  while (true) {
      // once we start here, ideally we should never return
  }
}

void Application::MtDataAppThread(const char* com_port) {
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

    int delay_time_in_sec{ 10 }; // configure sleep duration for thread
    char read_buffer[2048];
    char read_char{ 0 };
    int bytes_read = 0;

    while (true) {
        // flush before read
        serial_interface->Flush();
        // read latest serial data 1 by one between / and \
        
        int buf_index{ 0 };
        bool is_start{ false };
        bool is_end{ false };

        while (true) {

	  if (serial_interface->Read(&read_char, 1) != 0) {

	      // simple start end handling
	      if (read_char == '/') {
		is_start = true;
	      }

	      if (read_char == '\\') {
		is_end = true;
	      }
	      if (is_start == true) {
		read_buffer[buf_index] = read_char;
		buf_index++;
	      }
	      if (buf_index > 2 && is_end == true)
		break;
	  }
        }

        // just call the below method to get formatted output
        json_helper->GetJsonFormattedOutput(read_buffer, buf_index);
        // cleanup
        std::memset(read_buffer, 0, 2048);
        // goto sleep
        sleep(delay_time_in_sec);
    }
}

} // namespace mtdata_prj
