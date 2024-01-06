#pragma once

class GeometryHelper {
public:
    static MeshInfo CreateRectangle(void);
    static MeshInfo CreateCube(void);
    static MeshInfo CreatePlane(uint8_t numRows = 5, uint8_t numCols = 2);
};
