#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "external/imfilebrowser.h"
#include "../shader.hpp"

#include <functional>

class SettingsPanel
{
public:
    SettingsPanel(const std::function<void(const std::string &)> &callback);
    void Render(Shader *shader);

private:
    ImGui::FileBrowser _fileDialog;
    std::string _currentFile;
    std::function<void(const std::string &)> _onMeshLoad;
};