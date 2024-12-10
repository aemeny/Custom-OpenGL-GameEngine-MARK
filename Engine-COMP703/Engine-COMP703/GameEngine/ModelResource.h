/*
 *  File: ModelResource.h
 *  Author: Alex Emeny
 *  Date: December 10th, 2024 (Last Edited)
 *  Description: This file contains the ModelResource struct,
 *               It defines the function for loading a ModelHandler.
 *               This struct also handles storing and returning the created ModelHandler.
 */

#pragma once
#include "ResourceParent.h"

namespace GameEngine
{
    struct ModelResource : Resource
    {
        /* Creates a new Model Handler with a passed file address
         * stored in the Resource parent */
        void onLoad() override;

        /* Returns Model Handler struct */
        std::shared_ptr<GraphicsRenderer::ModelHandler> getModel();

    private:
        std::shared_ptr<GraphicsRenderer::ModelHandler> m_Model;
    };
}