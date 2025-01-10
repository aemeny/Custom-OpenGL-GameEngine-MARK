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
        m_GUIEntity = _GUIEntity;

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
        textCoords->add(glm::vec2(0.0f, 0.0f)); // Bottom left
        textCoords->add(glm::vec2(0.0f, 1.0f)); // Top left
        textCoords->add(glm::vec2(1.0f, 1.0f)); // Top right
        textCoords->add(glm::vec2(1.0f, 1.0f)); // Top right
        textCoords->add(glm::vec2(1.0f, 0.0f)); // Bottom right
        textCoords->add(glm::vec2(0.0f, 0.0f)); // Bottom left

        /* Add new Vbos to the Vao quad */
        m_quad = std::make_shared<GraphicsRenderer::Vao>();
        m_quad->addVbo(positon);
        m_quad->addVbo(textCoords);

        /* Make use of a default basic shader than can display GUI orthographic projections */
        m_shader = m_GUIEntity.lock()->m_corePtr.lock()->m_resources->
            load<ShaderResource>("../Shaders/Orphographics/vertexShader.glsl", "../Shaders/Orphographics/fragmentShader.glsl")->getShader();
    }

    void QuadRenderer::renderQuad()
    {
        std::weak_ptr<Camera> camera = m_GUIEntity.lock()->m_corePtr.lock()->m_mainCamera;
        std::weak_ptr<Transform> transform = m_GUIEntity.lock()->m_transformPtr;

        transform.lock()->updateMatrix();
        m_shader->bindShader(camera.lock()->getProjectionMatrix(), "u_Projection");
        m_shader->bindShader(transform.lock()->getModelMatrix(), "u_Model");

        m_shader->renderQuad(m_quad, m_texture);
    }

    void QuadRenderer::setTexture(std::string _textureFileAddress)
    {
        m_texture = m_GUIEntity.lock()->m_corePtr.lock()->m_resources->
            load<TextureResource>("../Samples/Textures/" + _textureFileAddress)->getTexture();
    }
}
