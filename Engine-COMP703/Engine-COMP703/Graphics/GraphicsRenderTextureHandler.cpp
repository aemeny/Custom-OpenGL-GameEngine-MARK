/*
 *  File: GraphicsRenderTextureHandler.cpp
 *  Author: Alex Emeny
 *  Date: January 3rd, 2025 (Last Edited)
 *  Description: This file implements the RenderTextureHandler struct.
 *               It defines the functions for generating and binding texture data from a camera output.
 */

#include "GraphicsRenderTextureHandler.h"
#include <stdexcept>

namespace GraphicsRenderer
{
    RenderTextureHandler::RenderTextureHandler(std::weak_ptr<Camera> _renderingCamera, int _textureWidth, int _textureHeight) :
        m_textureWidth(_textureWidth), m_textureHeight(_textureHeight), m_renderingCamera(_renderingCamera),
        m_dirty(true), m_textureID(0), m_fboID(0), m_rboID(0), m_clearColour(0.0f)
    {}

    RenderTextureHandler::~RenderTextureHandler()
    {
        if (m_fboID) glDeleteFramebuffers(1, &m_fboID);
        if (m_textureID) glDeleteTextures(1, &m_textureID);
        if (m_rboID) glDeleteRenderbuffers(1, &m_rboID);
    }

    void RenderTextureHandler::bind()
    {
        if (m_dirty)
        {
            m_dirty = false;

            /* Generate and bind frame buffer */
            glGenFramebuffers(1, &m_fboID);
            if (!m_fboID) throw std::runtime_error("Failed to generate frame buffer!");
            glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

            /* Generate and attach texture */
            glGenTextures(1, &m_textureID);
            glBindTexture(GL_TEXTURE_2D, m_textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);

            /* Generate and attach render buffer */
            glGenRenderbuffers(1, &m_rboID);
            glBindRenderbuffer(GL_RENDERBUFFER, m_rboID);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_textureWidth, m_textureHeight);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID);

            /* Check if frame buffer completed */
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                throw std::runtime_error("Frame buffer is not complete!");
            }
        }

        /* Bind the frame buffer */
        glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
    }

    void RenderTextureHandler::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GLuint RenderTextureHandler::getTextureID()
    {
        return m_textureID;
    }

    void RenderTextureHandler::generateMipmaps()
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RenderTextureHandler::setNewDimensions(int _textureWidth, int _textureHeight)
    {
        m_textureHeight = _textureHeight;
        m_textureWidth = _textureWidth;
        m_dirty = true;
    }
}