# V6 Game Engine

Linux Game Engine based on TheCherno Hazel Windows game engine [project](https://github.com/TheCherno/Hazel).

## Missing in Github

- glfw in src/v6/vendor/glfw
- imgui in src/v6/vendor/imgui
- glm in src/v6/vendor/glm

## Delete Below Here

- add latest stb-image.h from [github](https://github.com/nothings/stb/blob/master/stb_image.h) to the my-opengl include dir OR use existing
  - add pragma once to the top of this file
- cmake commands

```bash
mkdir build
cd build
cmake ..

# consider a debug build dir
# mkdir debug
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

## IMGUI setup

- copy cpp and header files source files from imgui into imgui-1.70
- add library in cmakelists
- include imgui in commits so above should exist already

## GLM setup

- copy glm directory from [glm-master](https://github.com/g-truc/glm) and place in vendor dir
- NOTE: this a header only library

## GLFW setup

- unzip GLFW to src/vendor
- install xorg-dev

```bash
sudo apt install xorg-dev
```

- try using [pkg-config](https://www.glfw.org/docs/latest/build_guide.html#build_link_pkgconfig) file: glfw3.pc

## GLAD setup

- generate a [loader](https://glad.dav1d.de/) currently with no extensions and place in vendor/glad
- 4.6 chosen for this project

## OpenGl Docs

- open gl [docs](http://docs.gl)
- consider using glDebugMessageCallback instead of the GLLogCall macro
- HP laptop driver: nvidia-340
  - version 340.107-0ubuntu0.18.04.2
  - hardware NVIDIA G86M GeForce 8600M GS
- green lantern driver: nvidia-390
  - version 390.116-0ubuntu0.18.04.1
  - hardware GK208B GeForce GT 710

```bash
glxinfo -B
glxinfo | grep "version"
```

## Misc

```bash
# inspect an archive static library
nm -C my-opengl/libmy-opengl.a | grep GLClearError
```
