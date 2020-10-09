# Among Us Taskbar Mask

A small utility to hide the Among Us taskbar when playing ([for more fun!](#motivation)).

![Preview](.readme/preview.gif?raw=true)

## Download

**Standalone executable (v0.0.1)**\
*Launch Taskbar Mask, then start Among Us (or vice versa).*
- Windows:
  - [64-bit x64 (.exe)](https://github.com/nathan818fr/among-us-taskbar-mask/releases/download/v0.0.1/among-us-taskbar-mask-win-x64.exe)
  - [32-bit x86 (.exe)](https://github.com/nathan818fr/among-us-taskbar-mask/releases/download/v0.0.1/among-us-taskbar-mask-win-x86.exe)

## Features

- Hide the taskbar (but displays the progress every 15 seconds).
- Supports different resolutions and windowed mode.
- Do not hide other windows when the game is in the background (eg. during an
  alt+tab).

## Known bugs & limitations

- *None*

## Motivation

When the taskbar is visible, it's easy to discover impostors by spying them
doing fake tasks:\
The task bar progresses when a crewmate completes a task; but this is not the
case with impostors. So by observing a player doing a few tasks we can quickly
exculpate or indict him depending on the progress (or not) of the task bar.

Hiding the taskbar therefore make the game more fun (especially in vocal) by
allowing imposters who fake their tasks well (with correct timings, etc) to
be like any crewmates!

Some sources:
- (en) [Reddit: Easy way to make the game more fun with friends you know!](https://www.reddit.com/r/AmongUs/comments/ibjz32/easy_way_to_make_the_game_more_fun_with_friends/)
- (fr) [Youtube: Comment Le Task Abuse ruine AMONG US](https://www.youtube.com/watch?v=AXsIWVDWM1Q)

## Technical details

### Main criteria

The program must be easy to download, share and use.

Its implementation must be simple; and easy to do on different platforms (since
Among Us also run on Linux - using proton).

### Approach used

Use a transparent window without border nor title bar to draw on the screen.

> This allows to create a small, standalone binary (statically linked, without using big toolkits/libraries).
> And it's functional on many platforms.

### Alternative approaches (not used)

- Inject into the game's OpenGL context to draw directly on it.
- Read and edit game memory to move/hide progress bar or it's value.
