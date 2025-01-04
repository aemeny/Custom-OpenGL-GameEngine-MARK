/*
 *  File: ModelHandler.h
 *  Author: Alex Emeny
 *  Date: December 17th, 2024 (Last Edited)
 *  Description: This file contains the ModelHandler struct,
 *               It defines the function for displaying a model with a texture and assigned shader.
 *               This struct also handles storing and setting handlers from the graphics renderer.
 */

#pragma once
#include "Component.h"
#include "TextureResource.h"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "../Graphics/GraphicsRenderTextureHandler.h"

namespace GameEngine
{
    struct ModelHandler : Component
    {
        void onDisplay() override;

        /* Loads the Graphics Renderer's ModelHandler resource */
        ModelHandler& setModel(std::string _modelFileAddress);
        /* Loads the Graphics Renderer's TextureHandler resource */
        ModelHandler& setTexture(std::string _textureFileAddress);
        /* Sets the Graphics Renderer's RenderTextureHandler */
        ModelHandler& setTexture(std::weak_ptr<GraphicsRenderer::RenderTextureHandler> _renterTexture);
        /* Loads the Graphics Renderer's ShaderHandler resource */
        ModelHandler& setShaders(std::string _vertShaderFileAddress, std::string _fragShaderFileAddress);

    private:
        /* Pointer references */
        std::shared_ptr<GraphicsRenderer::ModelHandler> m_model;
        std::shared_ptr<GraphicsRenderer::TextureHandler> m_texture;
        std::weak_ptr<GraphicsRenderer::RenderTextureHandler> m_renderTexture;
        std::shared_ptr<GraphicsRenderer::ShaderHandler> m_shader;
    };
}