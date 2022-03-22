#include "sybilengine/util/stopwatch.hpp" 

namespace sbl {
  Stopwatch::Stopwatch() 
  : m_startTime(Time::Now()) {
  }

  void Stopwatch::Reset() {
    m_startTime = Time::Now();
  }

  double Stopwatch::ElapsedTime() {
    return ElapsedTime(Unit::secs);
  }

  double Stopwatch::ElapsedTime(Unit unit) {
    double secs = Time::Now() - m_startTime;
    switch(unit) {
      case Unit::hrs : return secs / 3600;
      case Unit::mins: return secs / 60;
      case Unit::secs : return secs;
      case Unit::msecs : return secs * 1'000;
      case Unit::nsecs : return secs * 1'000'000;
    }
    return secs;
  }
}
