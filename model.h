#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
class Mesh;
class Material;
class Program;

class Model {
public:
    Model(const std::string& filename);
    ~Model();

public:
    void Draw(const Program* program);

private:
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    void ProcessNode(aiNode* node, const aiScene* scene);

private:
    std::vector<Mesh*> m_meshes;
    std::vector<Material*> m_materials;

public:
    bool IsSelect { false };
};
