#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model/model.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "ui_panel.hpp"

#include <string>
#include <stdexcept>
#include <memory>
#include <stdexcept>

class OpenGLContext
{
public:
    int Width;
    int Height;

    OpenGLContext(int width, int height, const std::string &windowName);
    ~OpenGLContext();

    Camera *GetCamera();
    void Run();

private:
    GLFWwindow *_window;

    std::unique_ptr<Model> _model;
    std::unique_ptr<Shader> _shader;
    std::unique_ptr<Camera> _camera;
    std::unique_ptr<UIPanel> _panel;

    void PreRender();
    void PostRender();

    static void OnWindowResize(GLFWwindow *window, int width, int height);
    static void OnScroll(GLFWwindow *window, double xoffset, double yoffset);
};