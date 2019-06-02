#include "app.h"

int main(int argc, char **argv) {

  v6::Log::init(); // can this be done in run()?
  LOG_CORE_WARN("Initialized log");
  LOG_INFO("Hello");
  LOG_CORE_ERROR("an error: {0}", "that needs to be logged");

  Sandbox *sandbox = new Sandbox();
  sandbox->run();
  delete sandbox;
  return 0;
}
