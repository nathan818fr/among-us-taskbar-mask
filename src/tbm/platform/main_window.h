#ifndef TBM_PLATFORM_MAIN_WINDOW_H_
#define TBM_PLATFORM_MAIN_WINDOW_H_

#include <functional>
#include <memory>
#include <string>
#include "tbm/platform/system.h"

namespace tbm {

class WindowPainter;
class MainWindowPrivate;

class MainWindow {
 public:
  MainWindow(const std::string &title, bool taskbar);

  virtual ~MainWindow();

  inline int width() const {
    return width_;
  }

  inline int height() const {
    return height_;
  }

  int run();

  void setUpdateFunction(const std::function<void()> &fct);

  void setDrawFunction(const std::function<void(WindowPainter *)> &fct);

  void setPosition(int left, int top, int width, int height, WindowHandle targetWindow);

  void hide();

 private:
  std::unique_ptr<MainWindowPrivate> p_;
  friend class MainWindowPrivate;

  int width_ = 0;
  int height_ = 0;
  std::function<void()> updateFct_;
  std::function<void(WindowPainter *)> drawFct_;
};

}  // namespace tbm

#endif  // TBM_PLATFORM_MAIN_WINDOW_H_
