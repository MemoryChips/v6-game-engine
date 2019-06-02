#pragma once

#ifdef V6_DEBUG
#define V6_ENABLE_ASSERTS
#endif

#ifdef V6_ENABLE_ASSERTS
#include <signal.h>
#define V6_ASSERT(x, ...)                                                      \
  {                                                                            \
    if (!(x)) {                                                                \
      LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__);                         \
      raise(SIGTRAP);                                                          \
    }                                                                          \
  }
#define V6_CORE_ASSERT(x, ...)                                                 \
  {                                                                            \
    if (!(x)) {                                                                \
      LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                    \
      raise(SIGTRAP);                                                          \
    }                                                                          \
  }
#else
#define V6_ASSERT(x, ...)
#define V6_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define V6_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
