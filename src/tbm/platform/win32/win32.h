#ifndef TBM_PLATFORM_WIN32_WIN32_H_
#define TBM_PLATFORM_WIN32_WIN32_H_

/*
 * Windows Header Files
 */
#define WIN32_LEAN_AND_MEAN  // exclude rarely-used stuff from Windows headers
#define NOMINMAX  // do not declare a min & max macros
#include <windows.h>
#include <shellapi.h>
#include <psapi.h>

/*
 * Nowide
 */
#include <nowide/convert.hpp>
using nowide::widen;
using nowide::narrow;

/*
 * Error handling
 */
#include <string>
void winFatalError(const std::string &fctName);

#endif  // TBM_PLATFORM_WIN32_WIN32_H_
