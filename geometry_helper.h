#pragma once

class GeometryHelper {
public:
    static MeshInfo CreateRectangle(void);
    static MeshInfo CreateCube(float scale = 1.0f);
    static MeshInfo CreatePlane(uint8_t numRows = 5, uint8_t numCols = 2);
    static MeshInfo CreateCylinder(float topRadius = 1.0f, float bottomRadius = 1.0f, float height = 1.0f, int segments = 10);
    static MeshInfo CreateSphere();
};
