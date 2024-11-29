/*
 *  File: GraphicsTextureHandler.h
 *  Author: Alex Emeny
 *  Date: November 19th, 2024
 *  Description: This file contains the TextureHandler struct,
 *               which is responsible for generating, binding, and uploading texture data.
 */

#pragma once
#include <GL/glew.h>

namespace GraphicsRenderer
{
    struct TextureHandler
    {
        /* Loads Texture data from passed file address */
        TextureHandler(const char* _fileAddress);
        /* Handles deleting the no longer needed texture */
        ~TextureHandler();

        /* Returns the textures ID value */
        GLuint getID() { return m_textureID; }

    private:
        /* Calls for the ID to be created, data uploaded to GPU and handles extra effects (e.g. alpha blending) */
        void generateTexture();
        /* Generates and binds the texture with the new created ID */
        void createTextureID();
        /* Sends a data call to be uploaded to the GPU */
        void uploadToGPU();

        GLuint m_textureID;             
        int m_width, m_height; // Texture dimensions
        unsigned char* m_textureData;   
    };
}