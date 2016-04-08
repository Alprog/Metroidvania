
#pragma once

#include <vector>
#include "Vertex.h"

class VertexBuffer
{
public:
    void Load();

    std::vector<Vertex> vertices;

    void* impl[2];
};
