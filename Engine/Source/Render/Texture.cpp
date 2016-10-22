
#include "Texture.h"
#include "Images.h"
#include "RenderManager.h"
#include "IRenderer.h"
#include "Impl.h"

Texture::Texture(std::string name)
    : name { name }
{
    load();
}

void Texture::load()
{
    auto& renderers = RenderManager::getInstance()->renderers;
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->createImpl(this);
    }
}
