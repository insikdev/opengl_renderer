#pragma once

class VertexArray;
class Buffer;

class Mesh {
public:
    Mesh(const MeshInfo& data);
    ~Mesh();

public:
    void Draw(void);

private:
    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<Buffer> m_vertexBuffer;
    std::unique_ptr<Buffer> m_indexBuffer;
};
