#pragma once

#include "core.h"
#include "events/event.h"
#include "log.h"
#include <string>
#include "core/timestep.h"

namespace v6 {

class Layer {
public:
  Layer(const std::string &name = "Layer");
  virtual ~Layer() = default;

  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate([[maybe_unused]] Timestep tf) {}
  virtual void onImGuiRender() {}
  virtual void onEvent([[maybe_unused]] Event &event) {}

  inline const std::string &GetName() const { return debugName; }

protected:
  std::string debugName;
};

} // namespace v6
