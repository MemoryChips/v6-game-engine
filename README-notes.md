# V6 Game Engine

## TODO

- TODO: Low

1. Find way to remove V6_DEBUG define for production build

## Build

- cmake to build

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

- TODO: below here

- glm - since we copy the glm sub dir of the repo do manual update

  - copy glm sub dir from [here](https://github.com/g-truc/glm/tree/master/glm)
  - consider sub module if easier

- imgui - use manual commmit and update

  - divide files into src and include and update
  - ignore all sub dirs
  - manual copy files from [here](https://github.com/ocornut/imgui)

## Precompile v6-pch.h

- This is currently not working since it is ignored by build

```bash
cd v6/include
g++ -c v6-pch.h -o v6-pch.h.gch -Wall -g -std=c++17
```

## Add Github - Switch to bit bucket and delete this repo

```bash
git remote add origin git@github.com:MemoryChips/v6-game-engine.git
git remote -v
```

## Misc

```bash
# inspect an archive static library
nm -C my-opengl/libmy-opengl.a | grep GLClearError
```
