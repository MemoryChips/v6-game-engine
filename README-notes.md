# V6 Game Engine

## Commit Status

- see core.h and log.h for v6 defines that differ from Hazel

- 10b4a3efbf4834e350326cf6ed21b2000e467090 - in progress

- 783d2568b6dd60157be82dbc1be582dcbda0f071 - done

- 49c526673eebc61b9d71f1849a02b81d5ad8f880 - done

- f52b813db65cd7275da56003c501914ad1c7515a - done

- 15c30d9e06a921ac130e05f3168fb55a374674d3 - done

- 72061ff6c5695587ce9d966dbf818130ba4d96da - done

- 6340cea5267e059dd3e8c98c3f4f94ac536bb2af - done

- 3c147806f0b253e4a288b64e65a81948d63f112e - added manually

- 888b3e8f7b07d16c6a52be0e49bd2526271cab36 - already present in my code

- 3352191dbcd5e18754be70b18a5e6744692a77ca - added manually

- a54b0742646493c6289a15eff036f2eb4cb1b894 - added manually possible error opengl error invalid operation with matrix starts here

- 5dc2ee187fae6a3efa1d13b61faf5ca67e3638bd - skipped

- c1d915e415be00207cab1b0ff3f05df28dfb6eb8 - Adds orthographic camera

```bash
git tag jul07b -a -m "Adds orthographic camera"
```

- dc9e38223eb71816ca1d34c4c54e60d88bf0512a - Adds RendererAPI and RenderCommand architecture

```bash
git tag jul07 -a -m "Commit dc9e Added RendererAPI and RenderCommand architecture"
```

- 982dcdfc5afe2ce74cb8297ad4e3c8fad79fc831 - skipped

- 9b75670ced984969806658a736c0709801ee3f1d merged; untagged

- cfe95cbee6a8fbc512723f0e6347d1a1babb7749 Layer onattach and onDetach are not called inside layer stack

  - above includes d8780e43bf3eb23694ca0c8f48638124f727b0e4 OnDetach must be called before removing from stack

  - above includes 1633bb5f85cfab6e273c11fbf4f722c5115cd4a0

  - 1adc... skipped

  - merged

```bash
git tag jun28 -a -m "Commit 0d29 OnDetach must be called before removing from stack"
```

- 7b06701a3eb9af0d00ca00f17d5d7e3d9e0863d5

  - more default destructors - skipped

- 4d818edb403d47f070e7a1481d5e8b1477049fbf

  - skipped does not differ from previous 1432...
  - also skipped: d5f68949fc39ede46545fe2e695891d5d997d45b for same reason

- 0d292a31d7b2827799388ffcfa677c90ed0ccb30 Adds vertex array support

  - merged

```bash
git tag jun12 -a -m "Commit 0d29 Adds vertex array support"
```

- e8eef169e95dcc9c2c1c64310c74f1a3d6c20c7e Added buffer layout descriptors for vertex buffers

  - includes log.h updates from 14325440d6894121e5a9c0063b5a54dec82445ee

```bash
git tag jun09 -a -m "Commit e8ee Added buffer layout descriptors for vertex buffers"
```

- 5221983ee2384fa213779cc5fa11445b6eb46a3a

  - skipped

- 0218724a644ea31663336e7a04424086eaab3787 Using default destructors over empty ones

  - merged

```bash
git tag jun06 -a -m "Commit 3787 Using default destructors over empty ones"
```

- 6481707b6821702dc5346d35886d8ea9ef6cb79e

  - skipped

- c81f2628d7cfd53dbbd651110fd83b60a65d3a09

  - skipped

- 7677da4c19f78d7aa5ef8414b71aba2957d0a139 Adds opengl buffer abstraction

  - merged

```bash
git tag jun02 -a -m "Commit 7677 adds opengl buffer abstraction"
```

- 76ae3b81ddcfacf0315608ae00627320ff98f0bb Our first shader

  - merged no tag

- f3e38fefcb43a473971fd551beca891b4cf807c6 skipped premake only

- e7b5157859db804d336641dce36bfa4ed163c751 Our first triangle

  - merged no tag

- 55fc4392f4bb44d94a54f09522d5545a86dfc48a Added OpenGL context class

  - merged tag may11

```bash
git tag may11 -a -m "Commit 55fc with ccc8 which I already had"
```

- 440d937aebed2315ebfdd66d8856567518038743

  - only changed float kept shared lib
  - merged with below commit

- 7c02b7863f1d70af88b7c447b223c9da4dc9e04a

  - merged tag feb23

```bash
git tag feb23 -a -m "Commit 7c02 merged but keeps shared lib"
```

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
