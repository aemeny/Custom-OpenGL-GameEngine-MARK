/*
 *  File: TextureResource.h
 *  Author: Alex Emeny
 *  Date: December 10th, 2024 (Last Edited)
 *  Description: This file contains the TextureResource struct,
 *               It defines the function for loading a TextureHandler.
 *               This struct also handles storing and returning the created TextureHandler.
 */

#pragma once
#include "ResourceParent.h"

namespace GameEngine
{
    struct TextureResource : Resource
    {
        /* Creates a new Texture Handler with a passed file address 
         * stored in the Resource parent */
        void onLoad() override;

        /* Returns Texture Handler struct */
        std::shared_ptr<GraphicsRenderer::TextureHandler> getTexture();

    private:
        std::shared_ptr<GraphicsRenderer::TextureHandler> m_Texture;
    };
}