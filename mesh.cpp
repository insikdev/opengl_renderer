#include "pch.h"
#include "mesh.h"
#include "gl_buffer.h"
#include "gl_vertex_array.h"

Mesh::Mesh(const MeshInfo& info)
{
    m_vertexArray = std::make_unique<VertexArray>();
    m_vertexBuffer = std::make_unique<Buffer>(GL_ARRAY_BUFFER, GL_STATIC_DRAW, info.vertices.data(), sizeof(Vertex), info.vertices.size());
    m_indexBuffer = std::make_unique<Buffer>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, info.indices.data(), sizeof(uint32_t), info.indices.size());

    m_vertexArray->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
    m_vertexArray->SetAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, normal));
    m_vertexArray->SetAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, uv));

    m_vertexArray->Unbind();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(void)
{
    m_vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexBuffer->GetCount()), GL_UNSIGNED_INT, 0);
    m_vertexArray->Unbind();
}
