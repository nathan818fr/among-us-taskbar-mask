#include "tbm/platform/win32/hdc_buffer.h"

namespace tbm {

HDCBuffer::~HDCBuffer() {
  release();
}

HDC HDCBuffer::begin(HDC hdcDst, int widthDst, int heightDst) {
  if (!hdc_ || hbmWidth_ != widthDst || hbmHeight_ != heightDst) {
    release();
    hdc_ = CreateCompatibleDC(hdcDst);
    if (!hdc_) {
      winFatalError("CreateCompatibleDC");
    }
    unsigned int nPlanes = GetDeviceCaps(hdc_, PLANES);
    unsigned int nBitCount = GetDeviceCaps(hdc_, BITSPIXEL);
    hbm_ = CreateBitmap(widthDst, heightDst, nPlanes, nBitCount, nullptr);
    if (!hbm_) {
      winFatalError("CreateBitmap");
    }
    hbmWidth_ = widthDst;
    hbmHeight_ = heightDst;
  }

  prevHdc_ = hdcDst;
  prevHbm_ = reinterpret_cast<HBITMAP>(SelectObject(hdc_, hbm_));
  return hdc_;
}

void HDCBuffer::end() {
  BitBlt(prevHdc_, 0, 0, hbmWidth_, hbmHeight_, hdc_, 0, 0, SRCCOPY);
  SelectObject(prevHdc_, prevHbm_);
  prevHdc_ = nullptr;
  prevHbm_ = nullptr;
}

void HDCBuffer::release() {
  DeleteObject(hbm_);
  hbm_ = nullptr;
  DeleteDC(hdc_);
  hdc_ = nullptr;
}

}  // namespace tbm
