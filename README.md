# OpenGL Model Viewer

A simple OpenGL Model Viewer written in C++ to get familiar with OpenGL and the libraries used within this project. This project serves a great reference to anyone interested in learning graphics programming.

![Preview](imgs/preview1.gif)

## Project Structure

Here is a brief overview of the project composition. It should help you understand how each part works in tandem.

- main.cpp
  - opengl_context.cpp
    - settings_panel.cpp
    - scene_panel.cpp
      - camera.cpp
      - model.cpp

## Building

```
mkdir build
cd build
cmake ..
make
```

## Libraries

- [glfw](https://github.com/glfw/glfw)
- [glad](https://github.com/Dav1dde/glad)
- [glm](https://github.com/Groovounet/glm)
- [imgui](https://github.com/ocornut/imgui)
- [assimp](https://github.com/assimp/assimp)
- [stb](https://github.com/nothings/stb)

## References

- https://learnopengl.com/Introduction
- https://github.com/jayanam/jgl_demos
- https://github.com/VictorGordan/opengl-tutorials
