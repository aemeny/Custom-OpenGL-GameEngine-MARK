#pragma once
#include "ResourceParent.h"

namespace GameEngine
{
    struct RenderTextureResource : Resource
    {
        /* Creates a new Render Texture Handler */
        void onLoad() override;

        /* Returns Render Texture Handler struct */
        std::shared_ptr<GraphicsRenderer::RenderTextureHandler> getTexture();

    private:
        std::shared_ptr<GraphicsRenderer::RenderTextureHandler> m_renderTexture;
    };
}