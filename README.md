# V6 Game Engine

Linux Game Engine based on TheCherno Hazel Windows game engine [project](https://github.com/TheCherno/Hazel).

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
