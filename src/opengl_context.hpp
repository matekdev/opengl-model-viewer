#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>

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

    void PreRender();
    void PostRender();
};