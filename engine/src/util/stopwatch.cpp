#include "sybilengine/util/stopwatch.hpp" 

namespace sbl {
  Stopwatch::Stopwatch() 
  : m_startTime(Time::Now()) {
  }

  void Stopwatch::Reset() {
    m_startTime = Time::Now();
  }

  double Stopwatch::ElapsedTime() {
    return ElapsedTime(TimeUnit::secs);
  }

  double Stopwatch::ElapsedTime(TimeUnit TimeUnit) {
    double secs = Time::Now() - m_startTime;
    switch(TimeUnit) {
      case TimeUnit::hrs : return secs / 3600;
      case TimeUnit::mins: return secs / 60;
      case TimeUnit::secs : return secs;
      case TimeUnit::msecs : return secs * 1'000;
      case TimeUnit::nsecs : return secs * 1'000'000;
    }
    return secs;
  }
}
