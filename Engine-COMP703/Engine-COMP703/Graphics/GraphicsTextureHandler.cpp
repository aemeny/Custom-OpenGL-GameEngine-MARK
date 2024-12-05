/*
 *  File: GraphicsTextureHandler.cpp
 *  Author: Alex Emeny
 *  Date: November 19th, 2024 (Last Edited)
 *  Description: This file implements the TextureHandler struct.
 *               It defines the functions for generating, binding, and uploading texture data.
 */

#include "GraphicsTextureHandler.h"

#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> // Public domain image loader - http://nothings.org/stb

namespace GraphicsRenderer
{
    /* Loads Texture data from passed file address */
    TextureHandler::TextureHandler(const char* _fileAddress) : m_width(0), m_height(0), m_textureID(0)
    {
        m_textureData = stbi_load(_fileAddress, &m_width, &m_height, NULL, 4);
        if (!m_textureData) 
            throw std::runtime_error("Couldn't Load Texture Data, Check File Address Is Correct");

        generateTexture();
    }

    /* Handles deleting the no longer needed texture */
    TextureHandler::~TextureHandler()
    {
        glDeleteTextures(1, &m_textureID);
    }

    /* Calls for the ID to be created, data uploaded to GPU and handles extra effects (e.g. alpha blending) */
    void TextureHandler::generateTexture()
    {
        createTextureID();
        uploadToGPU();

        // Generate Mipmap so the texture can be mapped correctly
        glGenerateMipmap(GL_TEXTURE_2D);

        // Unbind the texture as we are done operating on it
        glBindTexture(GL_TEXTURE_2D, 0);

        // Enables Alpha Blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    /* Generates and binds the texture with the new created ID */
    void TextureHandler::createTextureID()
    {
        // Checks if a texture ID already exists
        if (!m_textureID)
        {
            // Generates the texture and returns the created ID
            glGenTextures(1, &m_textureID);
            if (!m_textureID)
                throw std::runtime_error("Failed to allocate Texture ID");
            // If successful bind the texture
            glBindTexture(GL_TEXTURE_2D, m_textureID);
        }
    }

    /* Sends a data call to be uploaded to the GPU */
    void TextureHandler::uploadToGPU()
    {
        // Uploads the image data to the bound texture unit in the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);

        // Free the loaded data because we now have a copy on the GPU
        free(m_textureData);
    }
}