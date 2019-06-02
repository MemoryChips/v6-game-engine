#pragma once

#include "core.h"
#include "layer.h"

#include "v6-pch.h"
// #include "v6.h"
// #include <vector> // Why not precompiled v6-pch.h?

namespace v6 {

class LayerStack {
public:
  LayerStack();
  ~LayerStack();

  void pushLayer(Layer *layer);
  void pushOverlay(Layer *overlay);
  void popLayer(Layer *layer);
  void popOverlay(Layer *overlay);

  std::vector<Layer *>::iterator begin() { return layers.begin(); }
  std::vector<Layer *>::iterator end() { return layers.end(); }

private:
  std::vector<Layer *> layers;
  std::vector<Layer *>::iterator layerInsert;
};

} // namespace v6
