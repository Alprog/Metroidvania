
#include "Model.h"

#include "TextureManager.h"
#include "ShaderManager.h"
#include "Render/ConstantBuffer.h"
#include "Render/PipelineState.h"
#include "Render/RendererFrontend.h"

using base = Node;

Model::Model()
{
    mesh = createCubeMesh();
    renderState = new RenderState();

    renderState->vertexShader = ShaderManager::getInstance()->getShader("shadersTextured", Shader::Type::Vertex);
    renderState->pixelShader = ShaderManager::getInstance()->getShader("shadersTextured", Shader::Type::Pixel);
    renderState->texture = TextureManager::getInstance()->getTexture("skullbox.png");

    renderState->constantBuffer = new ConstantBuffer();

    renderState->link();
}

void Model::render(Matrix matrix, RendererFrontend* renderer)
{
    renderer->draw(mesh, matrix, renderState);
    base::render(matrix, renderer);
}
