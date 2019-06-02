#pragma once

#include "core.h"
#include "events/event.h"
#include <string>

namespace v6 {

class Layer {
public:
  Layer(const std::string &name = "Layer");
  virtual ~Layer();

  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate() {}
  virtual void onEvent(Event &event) {}

  inline const std::string &GetName() const { return debugName; }

protected:
  std::string debugName;
};

} // namespace v6
