#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <vector>
#include <string>
#include <iostream>

class ModelLoader
{
public:
    void static LoadObj(const std::string &filePath, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices);
};