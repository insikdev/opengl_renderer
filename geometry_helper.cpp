#include "pch.h"
#include "geometry_helper.h"

MeshInfo GeometryHelper::CreateRectangle(void)
{
    MeshInfo data;

    data.vertices = {
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
        { { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { 1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
    };

    data.indices = { 1, 0, 3, 1, 3, 2 };
    return data;
}

MeshInfo GeometryHelper::CreateCube(void)
{
    MeshInfo data;

    data.vertices = {
        // Front face
        { { -1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
        { { 1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },

        // Back face
        { { 1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
        { { -1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
        { { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },

        // Top face
        { { -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
        { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Bottom face
        { { -1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
        { { -1.0f, -1.0f, -1.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Right face
        { { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
        { { 1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },

        // Left face
        { { -1.0f, 1.0f, -1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -1.0f, -1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
        { { -1.0f, -1.0f, -1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } }
    };

    // CCW
    data.indices = {
        0, 3, 2, 0, 2, 1, // Front face
        4, 7, 6, 4, 6, 5, // Back face
        8, 11, 10, 8, 10, 9, // Top face
        12, 15, 14, 12, 14, 13, // Bottom face
        16, 19, 18, 16, 18, 17, // Right face
        20, 23, 22, 20, 22, 21 // Left face
    };

    return data;
}

MeshInfo GeometryHelper::CreatePlane(uint8_t numRows, uint8_t numCols)
{
    MeshInfo data;

    int height = numRows < 2 ? 2 : numRows;
    int width = numCols < 2 ? 2 : numCols;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            glm::vec3 pos(i, 0, -j);
            glm::vec3 normal(0.0f, 1.0f, 0.0f);
            glm::vec2 uv(static_cast<float>(i) / (width - 1), static_cast<float>(j) / (height - 1));
            Vertex v { pos, normal, uv };
            data.vertices.push_back(v);
        }
    }

    for (int j = 0; j < height - 1; j++) {
        for (int i = 0; i < width - 1; i++) {
            int bottomLeft = i + j * width;
            int bottomRight = bottomLeft + 1;
            int topLeft = bottomLeft + width;
            int topRight = topLeft + 1;

            // CCW
            data.indices.push_back(topLeft);
            data.indices.push_back(bottomLeft);
            data.indices.push_back(topRight);

            // CCW
            data.indices.push_back(topRight);
            data.indices.push_back(bottomLeft);
            data.indices.push_back(bottomRight);
        }
    }

    return data;
}
