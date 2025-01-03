/*
 *  File: TextureResource.cpp
 *  Author: Alex Emeny
 *  Date: December 10th, 2024 (Last Edited)
 *  Description: This file implements the methods declared TextureResource.h,
 *               It implements the function for loading a TextureHandler.
 */

#include "TextureResource.h"

namespace GameEngine
{
    /* Creates a new Texture Handler with a passed file address 
     * stored in the Resource parent */
    void TextureResource::onLoad()
    {
        m_texture = std::make_shared<GraphicsRenderer::TextureHandler>(getfileAddress().c_str());
    }

    /* Returns Texture Handler struct */
    std::shared_ptr<GraphicsRenderer::TextureHandler> TextureResource::getTexture()
    {
        return m_texture;
    }
}