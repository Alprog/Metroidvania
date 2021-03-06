
#pragma once

#include "dx.h"
#include "../Impl.h"
#include "../IndexBuffer.h"

class DXRenderer;

template <>
class Impl<IndexBuffer, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, IndexBuffer* indexBuffer);

    ComPtr<ID3D12Resource> indexBuffer;
    D3D12_INDEX_BUFFER_VIEW indexBufferView;
};
