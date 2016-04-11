
#pragma once

#include "Node.h"

#include "Mesh.h"
#include "Render/RenderState.h"
#include "Render/Renderer.h"
#include "Attributes.h"

struct [[Meta]] Model : public Node
{
    Model();

    virtual void Render(Matrix matrix, Renderer* renderer) override;

    Mesh* mesh;
    RenderState* renderState;

    [[Serialize]] [[Inspect]] std::string name;
};
