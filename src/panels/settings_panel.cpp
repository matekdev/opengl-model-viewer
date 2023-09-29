#include "settings_panel.hpp"

SettingsPanel::SettingsPanel(const std::function<void(const std::string &)> &callback)
{
    _onMeshLoad = callback;
    _currentFile = "< ... >";
    _fileDialog.SetTitle("Open mesh");
    _fileDialog.SetTypeFilters({".fbx", ".obj", ".gltf", ".dae", ".blend", ".3ds"});
}

void SettingsPanel::Render(Shader *shader)
{
    ImGui::ShowDemoWindow();
    ImGui::Begin("Settings");

    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {

        if (ImGui::Button("Open..."))
            _fileDialog.Open();

        ImGui::SameLine(0, 5.0f);
        ImGui::Text(_currentFile.c_str());
    }

    ImGui::End();

    _fileDialog.Display();
    if (!_fileDialog.HasSelected())
        return;

    auto file_path = _fileDialog.GetSelected().string();
    _currentFile = file_path.substr(file_path.find_last_of("/\\") + 1);
    _onMeshLoad(file_path);
    _fileDialog.ClearSelected();
}
