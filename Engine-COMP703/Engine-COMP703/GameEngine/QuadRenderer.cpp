/*
 *  File: QuadRenderer.cpp
 *  Author: Alex Emeny
 *  Date: January 10th, 2025 (Last Edited)
 *  Description: This file implements the methods declared QuadRenderer.h,
 *               It implements the function for displaying a quad with a texture and assigned shader.
 *               This struct also handles storing and setting handlers from the graphics renderer.
 */

#include "QuadRenderer.h"
#include "Core.h"

namespace GameEngine
{
    QuadRenderer::QuadRenderer(std::weak_ptr<Entity> _GUIEntity)
    {
        /* Creation of a default cube using Vbos */
        std::shared_ptr<GraphicsRenderer::Vbo> positon = std::make_shared<GraphicsRenderer::Vbo>();
        positon->add(glm::vec3(-0.5f, 0.5f, 0.0f));
        positon->add(glm::vec3(-0.5f, -0.5f, 0.0f));
        positon->add(glm::vec3(0.5f, -0.5f, 0.0f));

        positon->add(glm::vec3(0.5f, -0.5f, 0.0f));
        positon->add(glm::vec3(0.5f, 0.5f, 0.0f));
        positon->add(glm::vec3(-0.5f, 0.5f, 0.0f));

        /* Default cube texture coordinates */
        std::shared_ptr<GraphicsRenderer::Vbo> textCoords = std::make_shared<GraphicsRenderer::Vbo>();
        textCoords->add(glm::vec2(0.0f, 1.0f));
        textCoords->add(glm::vec2(0.0f, 0.0f));
        textCoords->add(glm::vec2(1.0f, 0.0f));
        textCoords->add(glm::vec2(1.0f, 0.0f));
        textCoords->add(glm::vec2(1.0f, 1.0f));
        textCoords->add(glm::vec2(0.0f, 1.0f));

        /* Add new Vbos to the Vao quad */
        m_quad = std::make_shared<GraphicsRenderer::Vao>();
        m_quad->addVbo(positon);
        m_quad->addVbo(textCoords);

        /* Make use of a default basic shader than can display GUI orthographic projections */
        m_shader = _GUIEntity.lock()->m_corePtr.lock()->m_resources->
            load<ShaderResource>("../Shaders/Orphographics/vertexShader.glsl", "../Shaders/Orphographics/fragmentShader.glsl")->getShader();
    }

    void QuadRenderer::renderQuad(GUI* _gui)
    {
    }

    void QuadRenderer::setTexture(std::string _textureFileAddress)
    {
    }
}
