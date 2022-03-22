#pragma once 

#include <string>

namespace sbl {
  class Logger {
  public:
    /*
     * STATIC METHODS
     */
    static void Init();
    static void Terminate();

    static void PrintLine(const std::string& string);
    static void Print(const std::string& string);
    
    static void PrintTime();
  };
}
