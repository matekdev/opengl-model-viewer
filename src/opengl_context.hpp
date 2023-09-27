#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model.hpp"
#include "shader.hpp"
#include "ui_panel.hpp"

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

    std::unique_ptr<Model> _model;
    std::unique_ptr<Shader> _shader;
    std::unique_ptr<UIPanel> _panel;

    void PreRender();
    void PostRender();
};