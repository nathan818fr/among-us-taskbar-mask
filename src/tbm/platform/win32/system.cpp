#include "tbm/platform/system.h"
#include <algorithm>
#include "tbm/platform/win32/win32.h"
#include "tbm/utils/math_utils.h"

namespace tbm {

int64_t System::getTimeMillis() {
  SYSTEMTIME time;
  GetSystemTime(&time);
  return (time.wSecond * 1000L) + time.wMilliseconds;
}

AmongUsWindow System::findAmongUsWindow() {
  HWND hwnd = FindWindowW(L"UnityWndClass", L"Among Us");
  if (hwnd) {
    RECT rect;
    if (GetClientRect(hwnd, &rect)
        && ClientToScreen(hwnd, reinterpret_cast<POINT *>(&rect.left))
        && ClientToScreen(hwnd, reinterpret_cast<POINT *>(&rect.right))) {
      int width = std::max(1, ncast<int>(rect.right - rect.left));
      int height = std::max(1, ncast<int>(rect.bottom - rect.top));
      return {
          reinterpret_cast<WindowHandle>(hwnd),
          {ncast<int>(rect.left), ncast<int>(rect.top), width, height}
      };
    }
  }
  return {nullptr};
}

}  // namespace tbm
