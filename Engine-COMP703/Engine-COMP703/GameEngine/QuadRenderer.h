/*
 *  File: QuadRenderer.h
 *  Author: Alex Emeny
 *  Date: January 10th, 2025 (Last Edited)
 *  Description: This file contains the QuadRenderer struct,
 *               It defines the function for displaying a quad with a texture and assigned shader.
 *               This struct also handles storing and setting handlers from the graphics renderer.
 */

#pragma once
#include "GUI.h"
#include "Camera.h"

namespace GameEngine
{
    struct QuadRenderer
    {
        QuadRenderer(std::weak_ptr<Entity> _GUIEntity);

        /* Render a quad based on GUI location and texture */
        void renderQuad();

        /* Loads the Graphics Renderer's TextureHandler resource */
        void setTexture(std::string _textureFileAddress);

    private:
        std::weak_ptr<Entity> m_GUIEntity;
        std::shared_ptr<GraphicsRenderer::Vao> m_quad;
        std::shared_ptr<GraphicsRenderer::ShaderHandler> m_shader;
        std::shared_ptr<GraphicsRenderer::TextureHandler> m_texture;
    };
}