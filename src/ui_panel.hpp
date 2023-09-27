#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class UIPanel
{
public:
    UIPanel(GLFWwindow *window);
    ~UIPanel();
    void PreRender();
    void Render();
    void PostRender();
};