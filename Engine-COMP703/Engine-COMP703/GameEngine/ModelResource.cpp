/*
 *  File: ModelResource.cpp
 *  Author: Alex Emeny
 *  Date: December 10th, 2024 (Last Edited)
 *  Description: This file implements the methods declared ModelResource.h,
 *               It implements the function for loading a ModelHandler.
 */

#include "ModelResource.h"

namespace GameEngine
{
    /* Creates a new Model Handler with a passed file address
     * stored in the Resource parent */
    void ModelResource::onLoad()
    {
        m_Model = std::make_shared<GraphicsRenderer::ModelHandler>(getfileAddress().c_str());
    }

    /* Returns Model Handler struct */
    std::shared_ptr<GraphicsRenderer::ModelHandler> ModelResource::getModel()
    {
        return m_Model;
    }
}