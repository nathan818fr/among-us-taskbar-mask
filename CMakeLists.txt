cmake_minimum_required(VERSION 3.17)
project(TBM)
set(EXECUTABLE_NAME Among_Us_Taskbar_Mask)

# Options

## Build target
option(TBM_WIN32 "Build for windows" OFF)
option(TBM_X11 "Build for linux (X11)" OFF)

if (NOT TBM_WIN32 AND NOT TBM_X11)
    if (WIN32)
        set(TBM_WIN32 ON)
    else ()
        set(TBM_X11 ON)
    endif ()
endif ()

if (TBM_WIN32)
    message(STATUS "Build target: WIN32")
    add_definitions("-DTBM_WIN32")
endif ()
if (TBM_X11)
    message(STATUS "Build target: X11")
    add_definitions("-DTBM_X11")
endif ()

# Compiler configuration
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (MSVC)
    ## Use unicode character set
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")

    ## Set optimization level
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
else ()
    message(FATAL_ERROR "Unsupported compiler!")
endif ()

# Dependencies

## Plog
include_directories(lib/plog_v1.1.5/include/)

## Nowide
if (TBM_WIN32)
    include_directories(lib/nowide_standalone_v11.0.0/include/)
    set(NOWIDE_SOURCES)
endif ()

# Sources
include_directories(src/)
set(GLOB_RECURSE HEADER_FILES "src/*.h")
set(SOURCE_FILES
        "src/tbm/among_us_geometry.cpp"
        "src/tbm/among_us_geometry.h"
        "src/tbm/app.cpp"
        "src/tbm/app.h"
        "src/tbm/constants.h"
        "src/tbm/log.h"
        "src/tbm/main.cpp"
        "src/tbm/platform/main_window.h"
        "src/tbm/platform/system.h"
        "src/tbm/platform/window_painter.h"
        "src/tbm/utils/geometry_types.h"
        "src/tbm/utils/math_utils.h"
        )

if (TBM_WIN32)
    list(APPEND SOURCE_FILES
            "src/tbm/platform/win32/hdc_buffer.cpp"
            "src/tbm/platform/win32/hdc_buffer.h"
            "src/tbm/platform/win32/main_window.cpp"
            "src/tbm/platform/win32/main_window_p.h"
            "src/tbm/platform/win32/system.cpp"
            "src/tbm/platform/win32/win32.cpp"
            "src/tbm/platform/win32/win32.h"
            "src/tbm/platform/win32/window_painter_hdc.cpp"
            "src/tbm/platform/win32/window_painter_hdc.h"
            )
endif ()

list(APPEND SOURCE_FILES ${NOWIDE_SOURCES})

# Executable
if (TBM_WIN32)
    add_executable(${EXECUTABLE_NAME} WIN32 ${SOURCE_FILES} resources/win32rc/resource.rc)
    set_property(TARGET ${EXECUTABLE_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else ()
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
endif ()
