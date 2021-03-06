#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>

namespace v6 {

struct ProfileResult {
  std::string Name;
  long long Start, End;
  uint32_t ThreadID;
};

struct InstrumentationSession {
  std::string Name;
};

class Instrumentor {
private:
  InstrumentationSession *m_CurrentSession;
  std::ofstream m_OutputStream;
  int m_ProfileCount;

public:
  Instrumentor() : m_CurrentSession(nullptr), m_ProfileCount(0) {}

  void beginSession(const std::string &name,
                    const std::string &filepath = "results.json") {
    m_OutputStream.open(filepath);
    writeHeader();
    m_CurrentSession = new InstrumentationSession{name};
  }

  void endSession() {
    writeFooter();
    m_OutputStream.close();
    delete m_CurrentSession;
    m_CurrentSession = nullptr;
    m_ProfileCount = 0;
  }

  void writeProfile(const ProfileResult &result) {
    if (m_ProfileCount++ > 0)
      m_OutputStream << ",";

    std::string name = result.Name;
    std::replace(name.begin(), name.end(), '"', '\'');

    m_OutputStream << "{";
    m_OutputStream << "\"cat\":\"function\",";
    m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
    m_OutputStream << "\"name\":\"" << name << "\",";
    m_OutputStream << "\"ph\":\"X\",";
    m_OutputStream << "\"pid\":0,";
    m_OutputStream << "\"tid\":" << result.ThreadID << ",";
    m_OutputStream << "\"ts\":" << result.Start;
    m_OutputStream << "}";

    m_OutputStream.flush();
  }

  void writeHeader() {
    m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
    m_OutputStream.flush();
  }

  void writeFooter() {
    m_OutputStream << "]}";
    m_OutputStream.flush();
  }

  static Instrumentor &get() {
    static Instrumentor *instance = new Instrumentor();
    return *instance;
  }
};

class InstrumentationTimer {
public:
  InstrumentationTimer(const char *name) : m_Name(name), m_Stopped(false) {
    m_StartTimepoint = std::chrono::high_resolution_clock::now();
  }

  ~InstrumentationTimer() {
    if (!m_Stopped)
      stop();
  }

  void stop() {
    auto endTimepoint = std::chrono::high_resolution_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(
                          m_StartTimepoint)
                          .time_since_epoch()
                          .count();
    long long end =
        std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
            .time_since_epoch()
            .count();

    uint32_t threadID =
        std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::get().writeProfile({m_Name, start, end, threadID});

    m_Stopped = true;
  }

private:
  const char *m_Name;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
  bool m_Stopped;
};

} // namespace v6

#ifdef V6_PROFILE
#define V6_PROFILE_BEGIN_SESSION(name, filepath)                               \
  ::v6::Instrumentor::get().beginSession(name, filepath)
#define V6_PROFILE_END_SESSION() ::v6::Instrumentor::get().endSession()
#define V6_PROFILE_SCOPE(name) ::v6::InstrumentationTimer timer##__LINE__(name);
#define V6_PROFILE_FUNCTION() V6_PROFILE_SCOPE(__FUNCTION__)
#else
#define V6_PROFILE_BEGIN_SESSION(name, filepath)
#define V6_PROFILE_END_SESSION()
#define V6_PROFILE_SCOPE(name)
#define V6_PROFILE_FUNCTION()
#endif
