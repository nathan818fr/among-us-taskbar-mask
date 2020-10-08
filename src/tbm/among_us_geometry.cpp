#include "tbm/among_us_geometry.h"
#include "tbm/utils/math_utils.h"

namespace tbm {

Rect<int> AmongUsGeometry::getHudRect(const Rect<int> &window_rect) {
  if (window_rect.width == 0 || window_rect.height == 0) {
    return {0, 0, 0, 0};
  }

  double hud_ratio = ncast<double>(window_rect.width) / ncast<double>(window_rect.height);
  hud_ratio = clamp(hud_ratio, 4.0 / 3.0, 16.0 / 9.0);
  int width, height;
  if (hud_ratio >= 1) {
    width = ceil<int>(ncast<double>(window_rect.height) * hud_ratio);
    height = ceil<int>(ncast<double>(width) / hud_ratio);
  } else {
    height = ceil<int>(ncast<double>(window_rect.width) / hud_ratio);
    width = ceil<int>(ncast<double>(height) * hud_ratio);
  }
  return {
      window_rect.left + center(width, window_rect.width),
      window_rect.top + center(height, window_rect.height),
      width,
      height
  };
}

Rect<int> AmongUsGeometry::getTaskbarRect(const Rect<int> &hud_rect) {
  double left = 11.0;
  double top = 15.0;
  double width = 798.0;
  double height = 70.0;
  double hPadding = 8.0;
  double vPatting = 11.0;
  double ratio = hud_rect.height / 1000.0;
  return {
      hud_rect.left + round<int>((left + hPadding) * ratio),
      hud_rect.top + round<int>((top + vPatting) * ratio),
      round<int>((width - hPadding * 2) * ratio),
      round<int>((height - vPatting * 2) * ratio)
  };
}

}  // namespace tbm
