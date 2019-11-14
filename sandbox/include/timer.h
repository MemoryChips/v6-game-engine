#include "v6-pch.h"
#include <chrono>

// TODO: Create timer.cpp

using namespace std::chrono;

template <typename Fn> class Timer {

public:
  Timer(const char *name, Fn &&func) : name(name), func(func), stopped(false) {
    startTimepoint = high_resolution_clock::now();
  }
  ~Timer() {
    if (!stopped)
      stop();
  }
  void stop() {
    auto endTimepoint = high_resolution_clock::now();
    long long start = time_point_cast<microseconds>(startTimepoint)
                          .time_since_epoch()
                          .count();
    long long end =
        time_point_cast<microseconds>(endTimepoint).time_since_epoch().count();
    stopped = true;
    float duration = (end - start) * 0.001;
    // LOG_INFO("{1} duration: {0} ms", duration, name);
    func({name, duration});
  }

private:
  const char *name;
  Fn func;
  time_point<system_clock, nanoseconds> startTimepoint;
  bool stopped;
};
