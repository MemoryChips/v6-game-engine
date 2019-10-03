#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace v6 {

std::shared_ptr<spdlog::logger> Log::coreLogger;
std::shared_ptr<spdlog::logger> Log::clientLogger;

void Log::init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  coreLogger = spdlog::stdout_color_mt("V6");
  clientLogger = spdlog::stdout_color_mt("APP");
  coreLogger->set_level(spdlog::level::trace);
  clientLogger->set_level(spdlog::level::trace);
}

} // namespace v6
