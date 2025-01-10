/*
 *  File: LineRenderer.cpp
 *  Author: Alex Emeny
 *  Date: December 23rd, 2024 (Last Edited)
 *  Description: This file contains the methods declared in LineRenderer.h
 *               It implements the functions for initializing new lines and rendering them.
 */

#include "LineRenderer.h"
#include "Core.h"
#include <iostream>

namespace GameEngine
{
    LineRenderer::LineRenderer(std::weak_ptr<Core> _core)
    {
        m_linesVao = std::make_shared<GraphicsRenderer::Vao>();

        m_shader = _core.lock()->m_resources->load<ShaderResource>
            ("../Shaders/Basic/vertexShader.glsl", "../Shaders/Basic/fragmentShader.glsl")
            ->getShader();

        m_numLinesCreated = 0;
    }

    void LineRenderer::renderDebugLines(std::weak_ptr<Core> _core)
    {
        if (m_numLinesCreated > 0)
        {
            /* Grab rendering camera */
            std::weak_ptr<Camera> camera = _core.lock()->getActiveRenderingCamera();

            /* Bind matrices to shader */
            m_shader->bindShader(camera.lock()->getProjectionMatrix(), "u_Projection");
            m_shader->bindShader(camera.lock()->getViewingMatrix(), "u_Viewing");

            /* Call for the lines to be rendered */
            m_shader->renderDebugLine(m_linesVao, m_numLinesCreated);
        }
    }

    void LineRenderer::initialize()
    {
        m_linesVao = std::make_shared<GraphicsRenderer::Vao>();

        m_shader = m_entity.lock()->m_corePtr.lock()->m_resources->load<ShaderResource>
            ("../Shaders/Basic/vertexShader.glsl", "../Shaders/Basic/fragmentShader.glsl")
            ->getShader();

        m_numLinesCreated = 0;
    }

    void LineRenderer::onDisplay()
    {
        if (m_numLinesCreated > 0)
        {
            /* Grab rendering camera */
            std::weak_ptr<Camera> camera = m_entity.lock()->m_corePtr.lock()->getActiveRenderingCamera();

            /* Bind matrices to shader */
            m_shader->bindShader(camera.lock()->getProjectionMatrix(), "u_Projection");
            m_shader->bindShader(camera.lock()->getViewingMatrix(), "u_Viewing");

            /* Call for the lines to be rendered */
            m_shader->renderDebugLine(m_linesVao, m_numLinesCreated);
        }
    }

    /* Adds a start and end position data to given vbo */
    void LineRenderer::addLine(std::weak_ptr<GraphicsRenderer::Vbo> _vbo, glm::vec3 _startPos, glm::vec3 _endPos)
    {
        for (size_t i = 0; i < m_linesVao->m_vbos.size(); i++)
        {
            /* Fine Vbo in stored Vbos */
            if (m_linesVao->m_vbos.at(i)->getIdentifierID() == _vbo.lock()->getIdentifierID())
            {
                m_linesVao->m_vbos.at(i)->add(_startPos);
                m_linesVao->m_vbos.at(i)->add(_endPos);

                m_numLinesCreated++;
            }
        }
    }

    void LineRenderer::clearLines(std::weak_ptr<GraphicsRenderer::Vbo> _vbo)
    {
        for (size_t i = 0; i < m_linesVao->m_vbos.size(); i++)
        {
            /* Fine Vbo in stored Vbos */
            if (m_linesVao->m_vbos.at(i)->getIdentifierID() == _vbo.lock()->getIdentifierID())
            {
                m_numLinesCreated -= m_linesVao->m_vbos[i]->getDataSize() / 6; // 6 = (start + end)2 * 3(XYZ)
                m_linesVao->m_vbos[i]->clearData();
            }
        }
    }
}