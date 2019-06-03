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

- add glad header before including GLFW

```c++
#include "glad/glad.h"
// prevent sorting of glad after glfw
#include "GLFW/glfw3.h"
```

## Add submodules - Consider this later

- spdlog - currently added manually to reduce to only include files

```bash
git submodule add https://github.com/gabime/spdlog.git src/v6/vendor/spdlog
# git mv v6/vendor/spdlog src/v6/vendor/spdlog # if put in the wrong place
```

- glm

```bash
git submodule add https://github.com/g-truc/glm.git src/v6/vendor/glm
```

- imgui

```bash
git submodule add https://github.com/TheCherno/imgui.git src/v6/vendor/imgui
```

- GLFW

```bash
#
# GLFW
#
# still under consideration - maybe just include the files needed from the open-gl project
git submodule add https://github.com/theCherno/glfw src/v6/vendor/glfw
# instead copied glfw files from opengl project - compiled earlier in the glfw dir
# currently this is ignored by git which is a problem to clone the project
# consider creating a make for glfw or use its cmake in here
```

## Imgui

```bash
# in directory src/vendor/imgui
# TODO: add this to build or create a submodule
# be sure to delete main.o and main.cpp if not needed for reference
# before building archive
cd src/v6/vendor/imgui/
g++-7 -Wall -c *.cpp -I../../glfw
ar rvs imgui.a *.o
```

## Add Github

```bash
git remote add origin git@github.com:MemoryChips/v6-game-engine.git
git remote -v
```
