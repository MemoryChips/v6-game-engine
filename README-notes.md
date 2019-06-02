# V6 Game Engine

## Clone to start a new project

```bash
# local clone
cd .. # go up one dir from this project dir
git clone hello-world new-project
git remote remove origin
git remote -v # verify remote is no longer hello world project
```

## Add submodules - Consider this later

- spdlog

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

## Add Premake

This did not work. Using manual make.

Add premake alpha 13 (or later) to folder vendor/bin at the top level NOT within src/v6/vendor.

Excluded from git.

Consider adding license file next to premake5.

```bash
./vendor/bin/premake5 gmake # run premake
make
```

## Add Github

```bash
git remote add origin git@github.com:MemoryChips/v6-game-engine.git
git remote -v
```
