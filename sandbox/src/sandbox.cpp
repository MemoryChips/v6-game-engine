#include "sandbox.h"

ExampleLayer::ExampleLayer() : Layer("Example") {}

void ExampleLayer::onUpdate() {}

void ExampleLayer::onImGuiRender() {}

void ExampleLayer::onEvent(v6::Event &e) {}

Sandbox::Sandbox(/* args */) { pushLayer(new ExampleLayer()); }
Sandbox::~Sandbox() {}