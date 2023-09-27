#include "model.hpp"

Model::Model(const std::string &filePath)
{
    Load(filePath, _vertices, _indices);
}

void Model::Load(const std::string &filePath, std::vector<glm::vec3> &vertices, std::vector<uint32_t> &indices)
{
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filePath, reader_config))
        throw std::runtime_error("TinyObjReader: " + reader.Error());

    if (!reader.Warning().empty())
        std::cout << "TinyObjReader: " << reader.Warning();

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();

    std::unordered_map<glm::vec3, uint32_t> uniqueVertices;

    for (const auto &shape : shapes)
    {
        for (const auto &index : shape.mesh.indices)
        {
            glm::vec3 position{
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]};

            if (uniqueVertices.count(position) == 0)
            {
                uniqueVertices[position] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(position);
            }

            indices.push_back(uniqueVertices[position]);
        }
    }
}
