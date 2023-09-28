#include "settings_panel.hpp"

SettingsPanel::SettingsPanel()
{
}

void SettingsPanel::Render(Shader *shader)
{
    // ImGui::ShowDemoWindow();
    ImGui::Begin("Settings");
    ImGui::Text("Hello, world %d", 123);
    ImGui::End();
}