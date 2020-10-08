#ifndef TBM_PLATFORM_WIN32_WINDOW_PAINTER_HDC_H_
#define TBM_PLATFORM_WIN32_WINDOW_PAINTER_HDC_H_

#include "tbm/platform/window_painter.h"
#include "tbm/platform/win32/win32.h"

namespace tbm {

class WindowPainterHDC : public WindowPainter {
 public:
  explicit WindowPainterHDC(HDC hdc);;

  void fillRect(int left, int top, int width, int height, int color) override;

 private:
  HDC hdc_;
};

}  // namespace tbm

#endif  // TBM_PLATFORM_WIN32_WINDOW_PAINTER_HDC_H_
