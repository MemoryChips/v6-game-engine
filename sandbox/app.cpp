#include "sandbox.h"

#ifndef V6_DEMO_VERSION
#define V6_DEMO_VERSION "x.y.z"
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

  v6::Log::init(); // can this be done in run()?
  LOG_INFO("Demo version: {0}", V6_DEMO_VERSION);

  Sandbox *sandbox = new Sandbox();
  sandbox->run();
  delete sandbox;

  return 0;
}
