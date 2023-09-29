#include "settings_panel.hpp"

SettingsPanel::SettingsPanel(const std::function<void(const std::string &)> &callback)
{
    _onMeshLoad = callback;
    _currentFile = "";
    _fileDialog.SetTitle("Open model");
    _fileDialog.SetTypeFilters({".fbx", ".obj", ".gltf", ".dae", ".blend", ".3ds"});
}

void SettingsPanel::Render(Camera *camera, Model *model, Shader *shader)
{
    ImGui::ShowDemoWindow();
    ImGui::Begin("Settings");

    if (ImGui::CollapsingHeader("Model", ImGuiTreeNodeFlags_DefaultOpen))
    {

        if (ImGui::Button("Open..."))
            _fileDialog.Open();

        ImGui::SameLine(0, 5.0f);
        ImGui::Text(_currentFile.c_str());

        ImGui::Checkbox("Wireframe", &model->WireFrame);
    }

    if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Button("Reset Position", ImVec2(-FLT_MIN, 0.0f)))
            camera->Reset();

        ImGui::DragFloat3("Position", glm::value_ptr(camera->Position), 0.25f, -FLT_MIN, FLT_MAX);
        ImGui::DragFloat3("Focus Point", glm::value_ptr(camera->FocusPoint), 0.25f, -FLT_MIN, FLT_MAX);
        ImGui::DragFloat("Zoom", &camera->Distance, 0.1f, -FLT_MIN, FLT_MAX);
        ImGui::SliderFloat("Rotation Speed", &camera->RotationSpeed, 0.0f, 5.0f);
    }

    if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text(("FPS: " + std::to_string((int)ImGui::GetIO().Framerate)).c_str());
        ImGui::Text(("Vertices:" + std::to_string(model->VertexCount())).c_str());
        ImGui::Text(("Triangles:" + std::to_string(model->TriangleCount())).c_str());
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
