/*
 *  File: ShaderResource.cpp
 *  Author: Alex Emeny
 *  Date: December 10th, 2024 (Last Edited)
 *  Description: This file implements the methods declared ShaderResource.h,
 *               It implements the function for loading a ShaderHandler.
 */

#include "ShaderResource.h"

namespace GameEngine
{
    /* Creates a new Shader Handler with a passed file address
     * stored in the Resource parent */
    void ShaderResource::onLoad()
    {
        m_Shader = std::make_shared<GraphicsRenderer::ShaderHandler>(getfileAddress().c_str());
    }

    /* Returns Shader Handler struct */
    std::shared_ptr<GraphicsRenderer::ShaderHandler> ShaderResource::getShader()
    {
        return m_Shader;
    }
}