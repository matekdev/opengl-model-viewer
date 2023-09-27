#pragma once

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <unordered_map>

class Model
{
public:
    Model(const std::string &filePath);
    void static Load(const std::string &filePath, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices);

private:
    std::vector<glm::vec3> _vertices;
    std::vector<uint32_t> _indices;
};