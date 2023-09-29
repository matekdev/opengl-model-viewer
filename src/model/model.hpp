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
    int VertexCount = 0;
    int TriangleCount = 0;
    bool WireFrame = false;

    Model();
    void Render(Shader *shader);
    void Load(const std::string &filePath);

private:
    std::vector<Mesh> _meshes;
    std::vector<Texture> _texturesLoaded;
    std::string _directory;

    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
    GLuint TextureFromFile(const std::string &path, const std::string &directory);
    void CalculateStats();
};