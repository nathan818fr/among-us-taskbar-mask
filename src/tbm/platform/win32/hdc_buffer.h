#ifndef TBM_PLATFORM_WIN32_HDC_BUFFER_H_
#define TBM_PLATFORM_WIN32_HDC_BUFFER_H_

#include "tbm/platform/window_painter.h"
#include "tbm/platform/win32/win32.h"

namespace tbm {

class HDCBuffer {
 public:
  virtual ~HDCBuffer();

  HDC begin(HDC hdcDst, int widthDst, int heightDst);

  void end();

 private:
  void release();

  HDC hdc_ = nullptr;
  HBITMAP hbm_ = nullptr;
  int hbmWidth_ = 0;
  int hbmHeight_ = 0;

  HDC prevHdc_ = nullptr;
  HBITMAP prevHbm_ = nullptr;
};

}  // namespace tbm

#endif  // TBM_PLATFORM_WIN32_HDC_BUFFER_H_
