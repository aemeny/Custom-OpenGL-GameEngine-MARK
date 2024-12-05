/*
 * File: GraphicsModelHandler.cpp
 * Author: Alex Emeny
 * Date: November 14th, 2024 (Last Edited)
 * Description: This file implements the methods declared in GraphicsModelHandler.h.
 *              It defines the functions for uploading .obj models to the GPU.
 */

#include "GraphicsModelHandler.h"

#include <iostream>

namespace GraphicsRenderer
{
    /* Uploads .obj model to GPU from given file address */
    ModelHandler::ModelHandler(std::string _fileAddress)
    {
        m_modelId = objLoadModel(_fileAddress, m_vertices, m_faces);
        if (!m_modelId)
        {
            std::cerr << "Failed to load model from " << _fileAddress << std::endl;
            throw std::runtime_error("Failed to load model");
        }
    }

    /* Calls upon the .obj model to be re-uploaded to the GPU */
    void ModelHandler::updateModel()
    {
        objUpdateModel(m_modelId, m_faces);
    }
}
