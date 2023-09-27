#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

#include <string>
#include <stdexcept>
#include <memory>

class OpenGLContext
{
public:
    OpenGLContext(int width, int height, const std::string &windowName);
    ~OpenGLContext();

    void Run();

private:
    GLFWwindow *_window;
    int _width;
    int _height;

    std::unique_ptr<Shader> _shader;

    void PreRender();
    void PostRender();
};