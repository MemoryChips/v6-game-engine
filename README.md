# V6 Game Engine

![V6](/v6/resources/Hazel_Logo_Text_Light_Square.png?raw=true "V6")

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

## Render API

- platform specific e.g. opengl, vulkan, direct3d, directx12, metal

  - Render Context
  - Swap chain
  - Framebuffer
  - Vertex Buffer
  - Index Buffer
  - Texture
  - Shader
  - Statess
  - Pipelines
  - Renderer passes

- platform agnostic

  - 2D and 3D renderer
    - Forward or deferred
  - Scene Graph
  - Sorting
  - Culling
  - Materials
  - LOD
  - Animation
  - Camera
  - VFX
  - PostFX
  - Other
    - reflectioins, ambient occlusion
