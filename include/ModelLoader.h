#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H
#include "string"
#include "vector"
#include "iostream"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Mesh.h"

class ModelLoader
{
public:
   static std::vector<Mesh> load(const std::string& path, const std::string& mtlPath,const std::string& texturePath = "")
{
    tinyobj::ObjReaderConfig config;
    config.triangulate = true;
    config.mtl_search_path = mtlPath;

    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(path, config)) {
        if (!reader.Error().empty()) {
            std::cerr << "OBJ ERR: " << reader.Error() << std::endl;
        }
        return {};
    }

    if (!reader.Warning().empty()) {
        std::cerr << "OBJ WARN: " << reader.Warning() << std::endl;
    }

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();
    const auto& materials = reader.GetMaterials();

    std::vector<Mesh> meshes;

    for (const auto& shape : shapes) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::unordered_map<std::string, GLuint> uniqueVertices;

        for (const auto& idx : shape.mesh.indices) {
            std::string key =
                std::to_string(idx.vertex_index) + "|" +
                std::to_string(idx.texcoord_index) + "|" +
                std::to_string(idx.normal_index);

            if (uniqueVertices.find(key) == uniqueVertices.end()) {
                Vertex v{};

                v.position = {
                    attrib.vertices[3 * idx.vertex_index + 0],
                    attrib.vertices[3 * idx.vertex_index + 1],
                    attrib.vertices[3 * idx.vertex_index + 2]
                };

                if (idx.texcoord_index >= 0) {
                    v.uv = {
                        attrib.texcoords[2 * idx.texcoord_index + 0],
                        attrib.texcoords[2 * idx.texcoord_index + 1]
                    };
                }

                // Нормаль
                if (idx.normal_index >= 0) {
                    v.normal = {
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2]
                    };
                }

                // Добавляем вершину и её индекс
                vertices.push_back(v);
                uniqueVertices[key] = (GLuint)vertices.size() - 1;
                indices.push_back((GLuint)vertices.size() - 1);
            } else {
                // Если вершина уже есть, используем её индекс
                indices.push_back(uniqueVertices[key]);
            }
        }

        // Загрузка текстур (если путь указан)
        std::vector<Texture> textures;
        if (!texturePath.empty()) {
            textures.emplace_back(texturePath.c_str(), GL_TEXTURE_2D, 0, true);
        }

        // Создаём меш и добавляем его в список
        meshes.emplace_back(vertices, indices, textures);

        // Отладочный вывод
        std::cout << "Mesh loaded: " << vertices.size() << " vertices, " << indices.size() << " indices." << std::endl;
    }

    return meshes;
}
};

#endif