/*
 *  File: LineRenderer.h
 *  Author: Alex Emeny
 *  Date: December 23rd, 2024 (Last Edited)
 *  Description: This file contains the LineRenderer struct
 *               It defines functions for initializing new lines and rendering them.
 */

#pragma once
#include "Component.h"
#include "ShaderResource.h"

namespace GameEngine
{
    struct LineRenderer : Component
    {
        void initialize() override;
        void onDisplay() override;

        void addLine();
        void clearLines();

    private:
        std::shared_ptr<GraphicsRenderer::ShaderHandler> m_shader;

        int m_numLinesCreated;
    };
}