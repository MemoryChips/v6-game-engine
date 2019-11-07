# V6 Game Engine

## Commit Status

- see core.h and log.h for v6 defines that differ from Hazel

- Nov 7
  - 8c35857cc442706ec0196d0298fefa11dfcbe0bf - in progress

- Nov 6
  - 6791c41095c85e200342c583e6100fdcf73ff933 - Done

- Oct 19
  - 0f583671c23c7a5e799269b791bc3d6220f99d22 - skip windows build only
  - 5edf68f3a973f76a93c0ef9eb576ff1fbcfbb9ea - Done
  - 3266b54fb00521a841efc2df2759a935336d7922 - skip PR template only
  - c0418194eb97fb5399a30c603e887322403cda28 - Done
  - 60cf553b80598b06716592147e8753fd2cdcaac1 - manually added

- Oct 17  
  - 7646edfed687b026f3eba9c428a56005197eed01 - manually added already but check later

- Oct 5 commits 12 total

  - 1,2,3 ignore.
  - fb841f8c0100c7c090e03dc62cab64c0bbd2ddff - causes compile issues; commented out
  - 5509204cca7e6607c20294b71b93e5f8264a5825 - done
  - a3ca6121084c2d69e8534a1b08a632282b5cb1c6 - done
  - .gitmodules - ignored since my submodule setup differs
  - 033af46fd59623f0a7ffa53344b4d3454ff28da8 - ignored for now until other platforms added
  - 4e0a190a31bd7672dbf8afcdc6c82a6a1fa0c816 - todo with code along if possible **
  - 14c3065f47d80a69bcf88b0c0a015b60d5ccb5a1 - done
  - 32c0f5643c835a6223bdc5d286e85dacf0fb8be6 - todo with code along **
  - bee34b9d9ad1ef0ee8c67b86059e1daceb3f9b24 - todo with code along **

- b62acd9c0c37c3b632bcf93f8ab404537cd0528b - done

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

- support to be added in version 3.16 of cmake

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
