# V6 Game Engine

## Commit Status

- see core.h and log.h for v6 defines that differ from Hazel

- b62acd9c0c37c3b632bcf93f8ab404537cd0528b - in progress

- 2b37c04ae1c7264f23f6af2d6c384ecc909f3b60 - manual done

- 734ea180bedd2334bdc3f1927635287be1e754ed - glfw updated; imgui NOT

- 0e034759705bb3b8ec5fa942e664798df9487469 - just started

- f50af9637e31595f49f21df3384224e40b5487fa - trivial done

- b576fd9f0326682da8ed8aa1a14abf25dc3bc630 - in progress

- 7d120fb4250ecdebdcdc93137bbec7413a9bb7e2 - done

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
make -j3 # to build
make clean
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
# GLFW add submodule
#
git submodule add https://github.com/glfw/glfw.git v6/vendor/glfw
#
# GLFW update submodule
#
git submodule update --remote --merge
# then commit and push
```

- spdlog - do manual update to only include files and to fix issues with the code

  - committed with v6 code
  - copy code [here](https://github.com/gabime/spdlog.git) to v6/vendor/spdlog
  - several changes needed to fix header file problems - locate these changes before updating

- imgui - use manual commmit and update

  - be sure to download docking branch
  - divide files into src and include and update
  - ignore all sub dirs
  - manually copy files from [here](https://github.com/ocornut/imgui) docking branch!
    - copy main dir .h into include; cpp into src
    - manually copy imgui_impl_opengl3.h and cpp from example dir into include and src
    - manually copy imgui_impl_glfw.h and cpp from example dir into include and src

    ```bash
    cd /home/robert/Training/cpp/v6-game-engine/v6/vendor/imgui/include
    cp /home/robert/Training/cpp/tmp/imgui/*.h .
    cp /home/robert/Training/cpp/tmp/imgui/examples/imgui_impl_opengl3.h .
    cp /home/robert/Training/cpp/tmp/imgui/examples/imgui_impl_glfw.h .
    cd ../src
    cp /home/robert/Training/cpp/tmp/imgui/*.cpp .
    cp /home/robert/Training/cpp/tmp/imgui/examples/imgui_impl_opengl3.cpp .
    cp /home/robert/Training/cpp/tmp/imgui/examples/imgui_impl_glfw.cpp .

    ```

- glm - since we copy the glm sub dir of the repo do manual update

  - copy glm sub dir from [here](https://github.com/g-truc/glm/tree/master/glm)
  - consider sub module if easier

## Precompile v6-pch.h

- This is currently not working since it is ignored by build

```bash
INCLUDES="-Iinclude -Isrc -Ivendor/spdlog/include -Ivendor/glm"
g++ $INCLUDES -c v6-pch.h -o v6-pch.h.gch -Wall -g -std=c++17
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
