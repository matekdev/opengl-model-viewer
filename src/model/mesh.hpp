#pragma once

#include "../shader.hpp"

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture
{
    GLuint id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices, std::vector<Texture> textures);
    void Render(Shader *shader);

private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _textures;
};