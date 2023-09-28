#pragma once

#include "mesh.hpp"
#include "../shader.hpp"

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include <vector>
#include <string>

// Thanks
// https://learnopengl.com/Model-Loading/Model
class Model
{
public:
    Model(const std::string &filePath);
    void Render(Shader *shader);

private:
    std::vector<Mesh> _meshes;
    std::vector<Texture> _texturesLoaded;
    std::string _directory;

    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
    GLuint TextureFromFile(const char *path, const std::string &directory);
};