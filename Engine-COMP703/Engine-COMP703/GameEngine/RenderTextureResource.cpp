#include "RenderTextureResource.h"

namespace GameEngine
{
    void RenderTextureResource::onLoad()
    {
        m_renderTexture = std::make_shared<GraphicsRenderer::RenderTextureHandler>(1, 1);
    }

    std::shared_ptr<GraphicsRenderer::RenderTextureHandler> RenderTextureResource::getTexture()
    {
        return m_renderTexture;
    }
}
