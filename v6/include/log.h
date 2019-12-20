#pragma once

// #include "my-stream.h"
#include "core.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

namespace v6 {

class Log {
private:
  static Ref<spdlog::logger> coreLogger;
  static Ref<spdlog::logger> clientLogger;

public:
  static void init();
  inline static Ref<spdlog::logger> &GetCoreLogger() { return coreLogger; }
  inline static Ref<spdlog::logger> &GetClientLogger() { return clientLogger; }
};

} // namespace v6

#define LOG_CORE_TRACE(...) ::v6::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...) ::v6::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...) ::v6::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::v6::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) ::v6::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...) ::v6::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::v6::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::v6::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::v6::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::v6::Log::GetClientLogger()->critical(__VA_ARGS__)
