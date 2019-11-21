#include "sandbox.h"

#ifndef V6_DEMO_VERSION
#define V6_DEMO_VERSION "x.y.z"
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

  v6::Log::init(); // can this be done in run()?
  LOG_INFO("Demo version: {0}", V6_DEMO_VERSION);

  V6_PROFILE_BEGIN_SESSION("Startup", "sandbox-startup.json");
  Sandbox *sandbox = new Sandbox();
  V6_PROFILE_END_SESSION();

  V6_PROFILE_BEGIN_SESSION("Runtime", "sandbox-runtime.json");
  sandbox->run();
  V6_PROFILE_END_SESSION();

  V6_PROFILE_BEGIN_SESSION("Shutdown", "sandbox-shutdown.json");
  delete sandbox;
  V6_PROFILE_END_SESSION();

  return 0;
}
