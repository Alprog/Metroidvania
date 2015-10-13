
#pragma once

#include "Node.h"
#include "string"
#include "Math/Transform2D.h"
#include "Meta/ITypeMeta.h"
#include "Attributes.h"

class _(Meta)__ Quad : public Node
{
    friend class Meta;

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Matrix matrix, Renderer* renderer) override;

    _(Serialize, Inspect)__ Vector2 Size;
    _(Serialize, Inspect)__ std::string Shader;
    _(Serialize, Inspect)__ std::string Texture;
};
