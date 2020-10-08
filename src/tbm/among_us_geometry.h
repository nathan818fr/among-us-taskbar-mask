#ifndef TBM_AMONG_US_GEOMETRY_H_
#define TBM_AMONG_US_GEOMETRY_H_

#include "tbm/utils/geometry_types.h"

namespace tbm {

class AmongUsGeometry {
 public:
  static Rect<int> getHudRect(const Rect<int> &window_rect);

  static Rect<int> getTaskbarRect(const Rect<int> &hud_rect);
};

}  // namespace tbm

#endif  // TBM_AMONG_US_GEOMETRY_H_
