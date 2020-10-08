#include "tbm/app.h"
#include "tbm/among_us_geometry.h"
#include "tbm/constants.h"
#include "tbm/platform/window_painter.h"
#include "tbm/utils/math_utils.h"

namespace tbm {

int App::run() {
  win_ = std::make_unique<MainWindow>("Taskbar Mask (" TBM_VERSION ")", true);
  win_->setUpdateFunction([this] { updateWindow(); });
  win_->setDrawFunction([this](WindowPainter *painter) { drawWindow(painter); });
  return win_->run();
}

void App::updateWindow() {
  auto amongusWin = System::findAmongUsWindow();
  if (amongusWin.handle != nullptr) {
    // game window found: set the bar position accordingly
    auto hud = AmongUsGeometry::getHudRect(amongusWin.rect);
    auto taskbar = AmongUsGeometry::getTaskbarRect(hud);
    win_->setPosition(taskbar.left, taskbar.top, taskbar.width, taskbar.height, amongusWin.handle);
  } else {
    // game window cannot be found: hide the bar
    win_->hide();
  }
}

void App::drawWindow(WindowPainter *painter) {
  if (win_->width() <= 0 || win_->height() <= 0) {
    return;
  }

  int color = 0x00000000;
  double progress = 1.0 - static_cast<double>(System::getTimeMillis() % 15000L) / 15000.0;
  int barWidth = win_->width();
  int barHeight = win_->height();
  int stepWidth = ceil<int>(barWidth * 0.2);
  int stepLeft = round<int>(-barWidth + (barWidth * 2 + stepWidth) * progress);
  int stepRight = stepLeft + stepWidth;

  // left part
  painter->fillRect(0, 0, stepLeft, barHeight, color);
  // right part
  painter->fillRect(stepRight, 0, barWidth - stepRight, barHeight, color);
}

}  // namespace tbm
