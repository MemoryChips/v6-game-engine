#include "layer-stack.h"
#include <algorithm>

namespace v6 {

LayerStack::LayerStack() {}

LayerStack::~LayerStack() {
  for (Layer *layer : layers) {
    layer->onDetach();
    delete layer;
  }
}

void LayerStack::pushLayer(Layer *layer) {
  layers.emplace(layers.begin() + layerInsertIndex, layer);
  layerInsertIndex++;
  // layer->onAttach();
}

void LayerStack::pushOverlay(Layer *overlay) {
  layers.emplace_back(overlay);
  // overlay->onAttach();
}

void LayerStack::popLayer(Layer *layer) {
  auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), layer);
  if (it != layers.begin() + layerInsertIndex) {
    layer->onDetach();
    layers.erase(it);
    layerInsertIndex--;
  }
}

void LayerStack::popOverlay(Layer *overlay) {
  auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
  // if (it != layers.end()) {
  if (it != layers.begin() + layerInsertIndex) {
    overlay->onDetach();
    layers.erase(it);
  }
}

} // namespace v6
