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

MeshInfo GeometryHelper::CreateCylinder(float topRadius, float bottomRadius, float height, int segments)
{
    MeshInfo data;

    float angle = glm::two_pi<float>() / segments;

    // bottom
    for (int i = 0; i < segments + 1; i++) {
        float theta = i * angle;
        float x = glm::cos(-theta) * bottomRadius;
        float z = glm::sin(-theta) * bottomRadius;

        glm::vec3 pos(x, 0.0f, z);
        glm::vec3 normal(glm::normalize(glm::vec3(x, 0, z)));
        glm::vec2 uv(static_cast<float>(i) / segments, 1.0f);

        data.vertices.push_back({ pos, normal, uv });
    }

    // top
    for (int i = 0; i < segments + 1; i++) {
        float theta = i * angle;
        float x = glm::cos(-theta) * topRadius;
        float z = glm::sin(-theta) * topRadius;

        glm::vec3 pos(x, height, z);
        glm::vec3 normal(glm::normalize(glm::vec3(x, 0, z)));
        glm::vec2 uv(static_cast<float>(i) / segments, 0.0f);

        data.vertices.push_back({ pos, normal, uv });
    }

    for (int i = 0; i < segments; i++) {
        int bottomLeft = i;
        int bottomRight = bottomLeft + 1;
        int topLeft = bottomLeft + segments + 1;
        int topRight = topLeft + 1;

        data.indices.push_back(topLeft);
        data.indices.push_back(bottomLeft);
        data.indices.push_back(bottomRight);

        data.indices.push_back(topLeft);
        data.indices.push_back(bottomRight);
        data.indices.push_back(topRight);
    }

    return data;
}

MeshInfo GeometryHelper::CreateSphere()
{
    MeshInfo data;

    float radius = 1.0f;
    int sectorCount = 50;
    int stackCount = 50;

    float x, y, z, xy; // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius; // vertex normal
    float s, t; // vertex texCoord

    float sectorStep = 2 * glm::pi<float>() / sectorCount;
    float stackStep = glm::pi<float>() / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = glm::pi<float>() / 2 - i * stackStep; // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle); // r * cos(u)
        z = radius * sinf(stackAngle); // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep; // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)
            glm::vec3 pos(x, y, z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            glm::vec3 normal(nx, ny, nz);

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            glm::vec2 uv(s, t);

            data.vertices.push_back({ pos, normal, uv });
        }
    }

    std::vector<int> lineIndices;
    int k1, k2;
    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1); // beginning of current stack
        k2 = k1 + sectorCount + 1; // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0) {
                data.indices.push_back(k1);
                data.indices.push_back(k2);
                data.indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stackCount - 1)) {
                data.indices.push_back(k1 + 1);
                data.indices.push_back(k2);
                data.indices.push_back(k2 + 1);
            }

            // store indices for lines
            // vertical lines for all stacks, k1 => k2
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            if (i != 0) // horizontal lines except 1st stack, k1 => k+1
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }
        }
    }

    return data;
}
