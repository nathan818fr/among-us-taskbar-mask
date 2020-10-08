#ifndef TBM_PLATFORM_WIN32_MAIN_WINDOW_P_H_
#define TBM_PLATFORM_WIN32_MAIN_WINDOW_P_H_

#include "tbm/platform/win32/win32.h"
#include "tbm/platform/win32/hdc_buffer.h"

namespace tbm {

class MainWindow;

class MainWindowPrivate {
 public:
  static LRESULT globalWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

  explicit MainWindowPrivate(MainWindow *v) : v_(v) {}

  LRESULT windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

 protected:
  void draw(HDC hdc);

 private:
  MainWindow *v_;
  friend class MainWindow;

  HBRUSH bgBrush_;
  LPCTSTR winClass_;
  HWND hwnd_;
  HDCBuffer hdcBuffer_;
};

}  // namespace tbm

#endif  // TBM_PLATFORM_WIN32_MAIN_WINDOW_P_H_
