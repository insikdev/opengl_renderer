#pragma once

class VertexArray;
class Buffer;
class Texture;
class Material;
class Program;

class Mesh {
public:
    Mesh(const MeshInfo& data);
    ~Mesh();

public:
    void Draw(const Program* program);
    static void ComputeTangents(std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

public:
    void SetMaterial(Material* material) { m_material = material; }

private:
    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<Buffer> m_vertexBuffer;
    std::unique_ptr<Buffer> m_indexBuffer;

private:
    Material* m_material {};
};
