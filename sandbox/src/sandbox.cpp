#include "sandbox.h"
// #include "example-layer.h"
#include "sandbox-2d.h"

using namespace v6;

Sandbox::Sandbox(/* args */) {
  // pushLayer(new ExampleLayer());
  pushLayer(new Sandbox2D());
}
Sandbox::~Sandbox() {}