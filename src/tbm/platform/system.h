#ifndef TBM_PLATFORM_SYSTEM_H_
#define TBM_PLATFORM_SYSTEM_H_

#include <cstdint>
#include "tbm/utils/geometry_types.h"

namespace tbm {

typedef void *WindowHandle;

struct AmongUsWindow {
  WindowHandle handle;
  Rect<int> rect;
};

class System {
 public:
  static int64_t getTimeMillis();

  static AmongUsWindow findAmongUsWindow();
};

}  // namespace tbm

#endif  // TBM_PLATFORM_SYSTEM_H_
