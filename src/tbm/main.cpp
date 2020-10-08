#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include "tbm/app.h"

int main() {
  plog::ConsoleAppender<plog::TxtFormatter> console_apd;
  plog::init(plog::debug, &console_apd);

  tbm::App app;
  return app.run();
}
