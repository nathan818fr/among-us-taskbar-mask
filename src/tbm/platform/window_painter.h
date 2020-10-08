#ifndef TBM_PLATFORM_WINDOW_PAINTER_H_
#define TBM_PLATFORM_WINDOW_PAINTER_H_

namespace tbm {

class WindowPainter {
 public:
  virtual ~WindowPainter() = default;

  virtual void fillRect(int left, int top, int width, int height, int color) = 0;
};

}  // namespace tbm

#endif  // TBM_PLATFORM_WINDOW_PAINTER_H_
