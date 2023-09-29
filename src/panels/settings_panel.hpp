#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_internal.h"

#include "external/imfilebrowser.h"
#include "../shader.hpp"
#include "../camera.hpp"
#include "../model/model.hpp"

#include <functional>

class SettingsPanel
{
public:
    SettingsPanel(const std::function<void(const std::string &)> &callback);
    void Render(Camera *camera, Model *model, Shader *shader);

private:
    ImGui::FileBrowser _fileDialog;
    std::string _currentFile;
    std::function<void(const std::string &)> _onMeshLoad;
};