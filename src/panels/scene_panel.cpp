#include "scene_panel.hpp"

ScenePanel::ScenePanel(GLFWwindow *window, int width, int height) : _window(window), _width(width), _height(height)
{
    _model = std::make_unique<Model>();
    _camera = std::make_unique<Camera>();

    // TODO: Remove
    LoadMesh("models/stanford-bunny.obj");

    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);

    glGenRenderbuffers(1, &_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void ScenePanel::Render(Shader *shader)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    glViewport(0, 0, _width, _height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _model->Render(shader);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Begin("Scene");
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    glm::vec2 size = {viewportPanelSize.x, viewportPanelSize.y};

    _camera->SetAspect(size.x / size.y);
    _camera->Update(shader);

    ImGui::Image(reinterpret_cast<void *>(_textureId), ImVec2{size.x, size.y}, ImVec2{0, 1}, ImVec2{1, 0});

    HandleMouseInput();

    ImGui::End();
}

void ScenePanel::LoadMesh(const std::string &filePath)
{
    _model->Load(filePath);
}

Model *ScenePanel::GetModel()
{
    return _model.get();
}

Camera *ScenePanel::GetCamera()
{
    return _camera.get();
}

void ScenePanel::HandleMouseInput()
{
    double x, y;
    glfwGetCursorPos(_window, &x, &y);
    GetCamera()->OnMouseMove(x, y, ImGui::IsWindowFocused(), Input::GetPressedButton(_window));
}
