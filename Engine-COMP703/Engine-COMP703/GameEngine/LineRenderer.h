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
#include "../Graphics/Vao.h"

namespace GameEngine
{
    struct LineRenderer : Component
    {
        /* If not component and within core */
        LineRenderer(std::weak_ptr<Core> _core);
        void renderDebugLines(std::weak_ptr<Core> _core);

        /* When used as a component within an Entity */
        void initialize() override;
        void onDisplay() override;

        /* Adds a start and end position data to given vbo */
        void addLine(std::weak_ptr<GraphicsRenderer::Vbo> _vbo, glm::vec3 _startPos, glm::vec3 _endPos);

        void clearLines(std::weak_ptr<GraphicsRenderer::Vbo> _vbo);

        /* Adds a new Vbo to the linesVao */
        std::weak_ptr<GraphicsRenderer::Vbo> addVbo()
        {
            std::shared_ptr<GraphicsRenderer::Vbo> rtn = std::make_shared<GraphicsRenderer::Vbo>();

            rtn->setVao(m_linesVao);

            m_linesVao->addVbo(rtn);

            return rtn;
        }

    private:
        /* Lines Vao that stores all the Vbos */
        std::shared_ptr<GraphicsRenderer::Vao> m_linesVao;

        /* Basic shader preset shader that handles basic coloured lines */
        std::shared_ptr<GraphicsRenderer::ShaderHandler> m_shader;

        int m_numLinesCreated;
    };
}