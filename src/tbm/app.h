#ifndef TBM_APP_H_
#define TBM_APP_H_

#include <memory>
#include "tbm/platform/main_window.h"

namespace tbm {

class App {
 public:
  int run();

 private:
  void updateWindow();

  void drawWindow(WindowPainter *painter);

  std::unique_ptr<MainWindow> win_;
};

}  // namespace tbm

#endif  // TBM_APP_H_
