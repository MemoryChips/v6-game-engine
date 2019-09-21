#pragma once

namespace v6 {
class Timestep {
public:
  Timestep(float time = 0.0f) : theTime(time) {}

  operator float() const { return theTime; }

  float getSeconds() const { return theTime; }
  float getMilliseconds() const { return theTime * 1000.0; }

private:
  float theTime;
};
} // namespace v6