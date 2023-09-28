#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "ui_context.hpp"
#include "panels/settings_panel.hpp"
#include "panels/scene_panel.hpp"

#include <string>
#include <stdexcept>
#include <memory>
#include <stdexcept>

class OpenGLContext
{
public:
    OpenGLContext(int width, int height, const std::string &windowName);
    ~OpenGLContext();

    Camera *GetCamera();
    void Run();

private:
    GLFWwindow *_window;

    int _width;
    int _height;

    std::unique_ptr<Shader> _shader;

    std::unique_ptr<UIContext> _uiContext;
    std::unique_ptr<ScenePanel> _scenePanel;
    std::unique_ptr<SettingsPanel> _settingsPanel;

    void PreRender();
    void PostRender();

    static void OnScroll(GLFWwindow *window, double xoffset, double yoffset);
};