#pragma once

#include "../shader.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class SettingsPanel
{
public:
    SettingsPanel();
    void Render(Shader *shader);
};