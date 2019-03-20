/*
 * main routine and fetching command line option
*/

#include "application.hpp"
#include <iostream>
#include <unistd.h>

void ShowUsage(char *argv[]) { std::cout << "Usage: "<<argv[0]<<" -p port" << std::endl; }

int main(int argc, char *argv[]) {
// command line parsing
  int opt;
  char *com_port;

  if (argc < 2) {
    ShowUsage(argv);
    return 0;
  }

  while ((opt = getopt(argc, argv, "p:")) != -1) {
    switch (opt) {
    case 'p':
      com_port = optarg;
      break;
    default:
      ShowUsage(argv);
      return 0;
    }
  }

  if (optind > argc) {
    std::cout << "Expected argument after options" << std::endl;
    return 0;
  }
  
  // pass the control to the mtdata applicaion
  mtdata_prj::Run(com_port);
  return 0;
}
