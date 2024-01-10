#include "pch.h"
#include "mesh.h"
#include "gl_buffer.h"
#include "gl_vertex_array.h"
#include "material.h"

Mesh::Mesh(const MeshInfo& info)
{
    ComputeTangents(const_cast<std::vector<Vertex>&>(info.vertices), info.indices);

    m_vertexArray = std::make_unique<VertexArray>();
    m_vertexBuffer = std::make_unique<Buffer>(GL_ARRAY_BUFFER, GL_STATIC_DRAW, info.vertices.data(), sizeof(Vertex), info.vertices.size());
    m_indexBuffer = std::make_unique<Buffer>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, info.indices.data(), sizeof(uint32_t), info.indices.size());

    m_vertexArray->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
    m_vertexArray->SetAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, normal));
    m_vertexArray->SetAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, uv));
    m_vertexArray->SetAttribute(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, tangent));

    m_vertexArray->Unbind();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(const Program* program)
{
    m_vertexArray->Bind();
    if (m_material) {
        m_material->SetToProgram(program);
    }
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexBuffer->GetCount()), GL_UNSIGNED_INT, 0);
    m_vertexArray->Unbind();
}

void Mesh::ComputeTangents(std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
    auto compute = [](const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec3& pos3, const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3) -> glm::vec3 {
        auto edge1 = pos2 - pos1;
        auto edge2 = pos3 - pos1;
        auto deltaUV1 = uv2 - uv1;
        auto deltaUV2 = uv3 - uv1;
        float det = (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        if (det != 0.0f) {
            auto invDet = 1.0f / det;
            return invDet * (deltaUV2.y * edge1 - deltaUV1.y * edge2);
        } else {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }
    };

    std::vector<glm::vec3> tangents;
    tangents.resize(vertices.size());
    memset(tangents.data(), 0, tangents.size() * sizeof(glm::vec3));

    for (size_t i = 0; i < indices.size(); i += 3) {
        auto v1 = indices[i];
        auto v2 = indices[i + 1];
        auto v3 = indices[i + 2];

        tangents[v1] += compute(vertices[v1].position, vertices[v2].position, vertices[v3].position, vertices[v1].uv, vertices[v2].uv, vertices[v3].uv);
        tangents[v2] = compute(vertices[v2].position, vertices[v3].position, vertices[v1].position, vertices[v2].uv, vertices[v3].uv, vertices[v1].uv);
        tangents[v3] = compute(vertices[v3].position, vertices[v1].position, vertices[v2].position, vertices[v3].uv, vertices[v1].uv, vertices[v2].uv);
    }

    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].tangent = glm::normalize(tangents[i]);
    }
}
