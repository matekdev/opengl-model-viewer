#pragma once

#include "model_loader.hpp"

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <unordered_map>

class Model
{
public:
    Model(const std::string &filePath);
    void Render();

private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    std::vector<glm::vec3> _vertices;
    std::vector<uint32_t> _indices;
};