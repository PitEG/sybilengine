//#include <easylogging++.h>

#include "sybilengine/debug/logger.hpp" 
#include "sybilengine/util/time.hpp" 

#include <iostream>

namespace sbl {

  /*
   * STATIC METHODS
   */
  void Logger::Init() {
  }

  void Logger::Terminate() {
  }

  void Logger::PrintLine(const std::string& string) {
    std::cout << string << std::endl;
  }

  void Logger::Print(const std::string& string) {
    std::cout << string;
  }

  void Logger::PrintTime() {
    PrintLine(std::to_string(sbl::Time::Now()));
  }

}
