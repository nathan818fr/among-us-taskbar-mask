#include "tbm/platform/win32/win32.h"
#include <nowide/args.hpp>
#include <cstdint>
#include "tbm/log.h"

int main(int argc, char **argv);

bool wWinRequireConsole(int argc, char **argv) {
  for (int i = 0; i < argc; ++i) {
    if (strcmp(argv[i], "--console") == 0) {
      return true;
    }
  }
  return false;
}

void wWinSetupConsole() {
  if (!AttachConsole(ATTACH_PARENT_PROCESS) && (!AllocConsole() || !AttachConsole(GetCurrentProcessId()))) {
    return;
  }
  freopen_s(reinterpret_cast<FILE **>(stdout), "CONOUT$", "w", stdout);
  freopen_s(reinterpret_cast<FILE **>(stderr), "CONOUT$", "w", stderr);
}

int APIENTRY wWinMain(_In_ HINSTANCE hinst, _In_opt_ HINSTANCE hprevinst, _In_ LPWSTR cmdline, _In_ int ncmdshow) {
  int argc = 0;
  char **argv = reinterpret_cast<char **>(CommandLineToArgvW(cmdline, &argc));
  if (!argv) {
    argc = 0;
  }
  nowide::args _(argc, argv);

  if (wWinRequireConsole(argc, argv)) {
    wWinSetupConsole();
  }
  return main(argc, argv);
}

void winFatalError(const std::string &fctName) {
  uint32_t errId = GetLastError();
  LPWSTR buf = nullptr;
  size_t bufLen = FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      nullptr, errId, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (LPWSTR) &buf, 0, nullptr);
  std::string errMessage(narrow(buf, bufLen));
  LocalFree(buf);

  LOGF << "Windows API call failed - " << fctName << ": " << errMessage;
  exit(1);
}
