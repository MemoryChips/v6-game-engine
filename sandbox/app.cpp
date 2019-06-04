#include "app.h"

#define V6_DEMO_VERSION "0.0.1"

int main(int argc, char **argv) {

  v6::Log::init(); // can this be done in run()?
  LOG_CORE_WARN("Initialized log");
  LOG_INFO("Hello from client application");
  LOG_INFO("Demo version: {0}", V6_DEMO_VERSION);
  LOG_CORE_ERROR("an error: {0}", "that needs to be logged");
  LOG_CORE_TRACE("a trace message: {0}", "that could be ignored");

  Sandbox *sandbox = new Sandbox();
  sandbox->run();
  delete sandbox;
  return 0;
}
