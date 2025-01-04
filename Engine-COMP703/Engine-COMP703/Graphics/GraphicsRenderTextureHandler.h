/*
 *  File: GraphicsRenderTextureHandler.h
 *  Author: Alex Emeny
 *  Date: January 3rd, 2025 (Last Edited)
 *  Description: This file contains the TextureHandler struct,
 *               which is responsible for generating and binding texture data from a camera output.
 */

#pragma once
#include "../GameEngine/Camera.h"

#include <GL/glew.h>


namespace GraphicsRenderer
{
    struct RenderTextureHandler
    {
        /* Sets default values for texture */
        RenderTextureHandler(std::weak_ptr<Camera> _renderingCamera, int _textureWidth, int _textureHeight);
        /* Cleans up IDs */
        ~RenderTextureHandler();

        /* Bind to render everything drawn to this texture */
        void bind();
        /* Unbind to stop rendering the scene to this texture */
        void unbind();

        void generateMipmaps();

        GLuint getTextureID();
        std::weak_ptr<Camera> getRenderingCamera() { return m_renderingCamera; }
        glm::vec3 getClearColour() { return m_clearColour; }
        bool getDirty() { return m_dirty; }
        GLuint getID() { return m_textureID; }

        void setClearColour(glm::vec3 _colour) { m_clearColour = _colour; }
        void setRenderingCamera(std::weak_ptr<Camera> _camera) { m_renderingCamera = _camera; }
        void setNewDimensions(int _textureWidth, int _textureHeight);

    private:
        GLuint m_textureID;
        GLuint m_fboID; // Frame buffer
        GLuint m_rboID; // Render buffer

        /* If the frame buffers and textures need to be compiled */
        bool m_dirty;

        int m_textureWidth;
        int m_textureHeight;

        /* Default colour when no texture is generated */
        glm::vec3 m_clearColour;

        /* Camera the texture is rendering from */
        std::weak_ptr<Camera> m_renderingCamera;
    };
}