
#include "RenderManager.h"

#include "Render/DX/DXRenderer.h"
#include "Render/GL/GLRenderer.h"

RenderManager::RenderManager()
{
    renderers.push_back(new DXRenderer());
    renderers.push_back(new GLRenderer());
}