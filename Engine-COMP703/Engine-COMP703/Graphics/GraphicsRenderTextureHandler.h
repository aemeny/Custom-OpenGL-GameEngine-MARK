/*
 *  File: GraphicsRenderTextureHandler.h
 *  Author: Alex Emeny
 *  Date: January 3rd, 2025 (Last Edited)
 *  Description: This file contains the TextureHandler struct,
 *               which is responsible for generating and binding texture data from a camera output.
 */

#pragma once
#include <GL/glew.h>

namespace GraphicsRenderer
{
    struct RenderTextureHandler
    {
        RenderTextureHandler(int _textureWidth, int _textureHeight);
        ~RenderTextureHandler();

        void bind();
        void unbind();

        GLuint getTextureID();
        void generateMipmaps();

    private:
        GLuint m_textureID;
        GLuint m_fboID; // Frame buffer
        GLuint m_rboID; // Render buffer

        bool m_dirty;

        int m_textureWidth;
        int m_textureHeight;
    };
}