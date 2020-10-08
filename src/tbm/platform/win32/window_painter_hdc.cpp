#include "tbm/platform/win32/window_painter_hdc.h"

namespace tbm {

WindowPainterHDC::WindowPainterHDC(HDC hdc) : hdc_(hdc) {}

void WindowPainterHDC::fillRect(int left, int top, int width, int height, int color) {
  if (width > 0 && height > 0) {
    RECT rect = {left, top, left + width, top + height};
    HBRUSH brush = CreateSolidBrush(color);
    if (!brush) {
      winFatalError("CreateSolidBrush");
    }
    FillRect(hdc_, &rect, brush);
    DeleteObject(brush);
  }
}

}  // namespace tbm
