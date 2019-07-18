namespace v6 {
class Timestep {
public:
  Timestep(double time) : theTime(time) {}
  double getSeconds() { return theTime; }
  double getMilliseconds() { return theTime * 1000.0; }

private:
  double theTime;
};
} // namespace v6