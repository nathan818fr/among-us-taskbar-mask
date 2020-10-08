#include "tbm/platform/main_window.h"
#include <iostream>
#include <memory>
#include <string>
#include "tbm/platform/win32/main_window_p.h"
#include "tbm/platform/win32/window_painter_hdc.h"
#include "tbm/log.h"

#define TBM_MAINWINDOW_ALPHA_COLOR 0x007F3FFF
#define TBM_MAINWINDOW_UPDATEWINDOW_EVENT 1
#define TBM_MAINWINDOW_REDRAW_EVENT 2

namespace tbm {

MainWindow::MainWindow(const std::string &title, bool taskbar) : p_(std::make_unique<MainWindowPrivate>(this)) {
  // Register background brush.
  p_->bgBrush_ = CreateSolidBrush(TBM_MAINWINDOW_ALPHA_COLOR);
  if (!p_->bgBrush_) {
    winFatalError("CreateSolidBrush");
  }

  // Register window class.
  p_->winClass_ = L"TbmMainWindowClass";
  WNDCLASS wc;
  wc.style = 0;
  wc.lpfnWndProc = reinterpret_cast<WNDPROC>(&MainWindowPrivate::globalWindowProc);
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.hIcon = nullptr;
  wc.hCursor = nullptr;
  wc.hbrBackground = p_->bgBrush_;
  wc.lpszMenuName = nullptr;
  wc.lpszClassName = p_->winClass_;
  if (!RegisterClass(&wc)) {
    winFatalError("RegisterClass");
  }

  // Create window.
  p_->hwnd_ = CreateWindow(
      p_->winClass_, widen(title).c_str(),
      0, 0, 0, 0, 0, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
  if (!p_->hwnd_) {
    winFatalError("CreateWindow");
  }

  // Store the MainWindow pointer in GWLP_USERDATA.
  // It will be used by globalWindowProc.
  SetWindowLongPtr(p_->hwnd_, GWLP_USERDATA, (LONG_PTR)
  this);

  // Remove all window decoration (title bar, borders) and made it transparent.
  SetWindowLong(p_->hwnd_, GWL_STYLE, 0);
  SetWindowLong(p_->hwnd_, GWL_EXSTYLE, GetWindowLong(p_->hwnd_, GWL_EXSTYLE)
      | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_NOACTIVATE | (taskbar ? WS_EX_APPWINDOW : 0));
  SetLayeredWindowAttributes(p_->hwnd_, TBM_MAINWINDOW_ALPHA_COLOR, 0, LWA_COLORKEY);

  // And move the window offscreen.
  hide();
}

MainWindow::~MainWindow() {
  if (p_->hwnd_) DestroyWindow(p_->hwnd_);
  if (p_->winClass_) UnregisterClass(p_->winClass_, GetModuleHandle(nullptr));
  if (p_->bgBrush_) DeleteObject(p_->bgBrush_);
}

int MainWindow::run() {
  // Show the window.
  ShowWindow(p_->hwnd_, SW_SHOWNOACTIVATE);

  // And also focus it. This will not really focus the windows since it has the WS_EX_NOACTIVATE flag but it will force
  // it to be always shown (otherwise sometimes the window remains in the background... even with the HWND_TOPMOST!).
  SetFocus(p_->hwnd_);

  // Run the UI event loop.
  MSG msg;
  int msgr;
  while ((msgr = GetMessage(&msg, nullptr, 0, 0)) != 0) {
    if (msgr == -1) {
      winFatalError("GetMessage");
    }

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}

void MainWindow::setUpdateFunction(const std::function<void()> &fct) {
  updateFct_ = fct;
  SetTimer(p_->hwnd_, TBM_MAINWINDOW_UPDATEWINDOW_EVENT, (1000 / 60) * 5, nullptr);
}

void MainWindow::setDrawFunction(const std::function<void(WindowPainter *)> &fct) {
  drawFct_ = fct;
  SetTimer(p_->hwnd_, TBM_MAINWINDOW_REDRAW_EVENT, (1000 / 60), nullptr);
}

void MainWindow::setPosition(int left, int top, int width, int height, WindowHandle targetWindow) {
  HWND insertAfter;
  if (!targetWindow) {
    insertAfter = nullptr;
  } else {
    insertAfter = HWND_TOPMOST;
    if (targetWindow != GetForegroundWindow()) {
      HWND prevWindow = GetWindow(reinterpret_cast<HWND>(targetWindow), GW_HWNDPREV);
      if (prevWindow == p_->hwnd_) {
        prevWindow = GetWindow(prevWindow, GW_HWNDPREV);
      }
      if (prevWindow && prevWindow != targetWindow && prevWindow != p_->hwnd_) {
        insertAfter = prevWindow;
      }
    }
  }

  SetWindowPos(p_->hwnd_, insertAfter, left, top, width, height, 0);
  width_ = width;
  height_ = height;
}

void MainWindow::hide() {
  // Move the window offscreen to hide it.
  setPosition(-65536, -65536, 0, 0, nullptr);
}

LRESULT MainWindowPrivate::globalWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  auto window = reinterpret_cast<MainWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
  if (window) {
    return window->p_->windowProc(hwnd, message, wParam, lParam);
  }
  return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT MainWindowPrivate::windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_DESTROY: {
      // Quit application when the window is closed.
      PostQuitMessage(0);
      return 0;
    }

    case WM_TIMER: {
      if (wParam == TBM_MAINWINDOW_UPDATEWINDOW_EVENT) {
        if (v_->updateFct_) v_->updateFct_();
      } else if (wParam == TBM_MAINWINDOW_REDRAW_EVENT) {
        HDC hdc = GetDC(hwnd_);
        if (!hdc) {
          winFatalError("HDC");
        }
        this->draw(hdc);
        ReleaseDC(hwnd_, hdc);
      }
      return 0;
    }

    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);
      if (!hdc) {
        winFatalError("BeginPaint");
      }
      this->draw(hdc);
      EndPaint(hwnd, &ps);
      return 0;
    }

    case WM_ERASEBKGND: {
      // Prevent the background to be erased (it's handled manually when drawing).
      return 1;
    }

    default:break;
  }
  return DefWindowProc(hwnd, message, wParam, lParam);
}

void MainWindowPrivate::draw(HDC hdc) {
  HDC hdcPaint = hdcBuffer_.begin(hdc, v_->width(), v_->height());
  WindowPainterHDC painter(hdcPaint);

  // Erase the background...
  RECT rect = {0, 0, v_->width(), v_->height()};
  FillRect(hdcPaint, &rect, bgBrush_);

  // Then draw!
  if (v_->drawFct_) v_->drawFct_(&painter);

  hdcBuffer_.end();
}

}  // namespace tbm
