/*
 *  File: ShaderResource.h
 *  Author: Alex Emeny
 *  Date: December 10th, 2024 (Last Edited)
 *  Description: This file contains the ShaderResource struct,
 *               It defines the function for loading a ShaderHandler.
 *               This struct also handles storing and returning the created ShaderHandler.
 */

#pragma once
#include "ResourceParent.h"

namespace GameEngine
{
    struct ShaderResource : Resource
    {
        /* Creates a new Shader Handler with a passed file address
         * stored in the Resource parent */
        void onLoad() override;

        /* Returns Shader Handler struct */
        std::shared_ptr<GraphicsRenderer::ShaderHandler> getShader();

    private:
        std::shared_ptr<GraphicsRenderer::ShaderHandler> m_Shader;
    };
}