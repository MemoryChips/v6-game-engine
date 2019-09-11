# V6 Game Engine

## Commit Status

- see core.h and log.h for v6 defines that differ from Hazel

- f50af9637e31595f49f21df3384224e40b5487fa - trivial done

- b576fd9f0326682da8ed8aa1a14abf25dc3bc630 - in progress

- 7d120fb4250ecdebdcdc93137bbec7413a9bb7e2 - done

- 30b5c242986c67ab20709980f88ca115e65e1261 - done

- 9cbad6e514e800dd2337ed88403449f445981e3a - done

- e8b2ad932372b0121349f34df14e743bb95773fc - done

- 670e86fe430d16a3eb391378db8239775ffc5cca - added to make task

- 070571c41354d488a8c66ceab21044bd5dcd8043 - skipped

- 10b4a3efbf4834e350326cf6ed21b2000e467090 - done

- 783d2568b6dd60157be82dbc1be582dcbda0f071 - done

## TODO

- High Priority

- Normal

1. Add warnings output to imgui build as Sandbox and v6 have
1. Consider going to static library

- Low Priority

1. Find way to remove V6_DEBUG define for production build

## Build

- cmake to build

  - run cmake-debug or cmake-prod to setup make file
  - run make task

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

## Setup Notes

- create glad loader [here](https://glad.dav1d.de/)

  - creates glad.c and glad.h
  - add glad header before including GLFW in application.cpp

```c++
#include "glad/glad.h"
// prevent sorting of glad after glfw
#include "GLFW/glfw3.h"
```

## Add submodules and manual copied code

- stb-image.h

  - add latest stb-image.h from [github](https://github.com/nothings/stb/blob/master/stb_image.h) to the v6/vendor/stb-image dir
  - add pragma once to the top of this file

- GLFW

```bash
#
# GLFW
#
git submodule add https://github.com/glfw/glfw.git v6/vendor/glfw
```

- spdlog - do manual update to only include files and to fix issues with the code

  - committed with v6 code
  - copy code [here](https://github.com/gabime/spdlog.git) to v6/vendor/spdlog
  - several changes needed to fix header file problems - locate these changes before updating

- imgui - use manual commmit and update

  - divide files into src and include and update
  - ignore all sub dirs
  - manual copy files from [here](https://github.com/ocornut/imgui)

- glm - since we copy the glm sub dir of the repo do manual update

  - copy glm sub dir from [here](https://github.com/g-truc/glm/tree/master/glm)
  - consider sub module if easier

## Precompile v6-pch.h

- This is currently not working since it is ignored by build

```bash
cd v6/include
g++ -c v6-pch.h -o v6-pch.h.gch -Wall -g -std=c++17
```

## Add Github

```bash
git remote add github git@github.com:MemoryChips/v6-game-engine.git
git remote -v
git push -u github master
```

## Misc

```bash
# inspect an archive static library
nm -C my-opengl/libmy-opengl.a | grep GLClearError
```
