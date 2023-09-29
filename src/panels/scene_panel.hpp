#pragma once

#include "../shader.hpp"
#include "../camera.hpp"
#include "../model/model.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <memory>

class ScenePanel
{
public:
    ScenePanel(int width, int height);
    void Render(Shader *shader);
    void LoadMesh(const std::string &filePath);
    Camera *GetCamera();
    Model *GetModel();

private:
    int _width;
    int _height;

    GLuint _vao;
    GLuint _vbo;
    GLuint _fbo;
    GLuint _rbo;
    GLuint _textureId;

    std::unique_ptr<Camera> _camera;
    std::unique_ptr<Model> _model;
};