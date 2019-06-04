# V6 Game Engine

## Setup Notes

- TODO: Low

1. Find way to remove V6_DEBUG define for production build

- cmake

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

- add glad header before including GLFW in application.cpp

```c++
#include "glad/glad.h"
// prevent sorting of glad after glfw
#include "GLFW/glfw3.h"
```

## Add submodules - Consider this later

- GLFW

```bash
#
# GLFW
#
git submodule add https://github.com/glfw/glfw.git v6/vendor/glfw
```

- spdlog - currently added manually to reduce to only include files and to fix issues with the code
  - committed with v6 code

```bash
git submodule add https://github.com/gabime/spdlog.git v6/vendor/spdlog
# git mv v6/vendor/spdlog src/v6/vendor/spdlog # if put in the wrong place
```

- TODO: below here

- glm - since we copy the glm sub dir of the repo do manual update

  - copy glm sub dir from [here](https://github.com/g-truc/glm/tree/master/glm)

- imgui - use manual commmit and update
  - divide files into src and include and update
  - ignore all sub dirs
  - manual copy files from [here](https://github.com/ocornut/imgui)

## Add Github - Switch to bit bucket and delete this repo

```bash
git remote add origin git@github.com:MemoryChips/v6-game-engine.git
git remote -v
```
