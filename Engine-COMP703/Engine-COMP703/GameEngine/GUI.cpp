/*
 *  File: GUI.cpp
 *  Author: Alex Emeny
 *  Date: January 10th, 2025 (Last Edited)
 *  Description: This file implements the methods declared ModelHandler.h,
 *               It implements the function for displaying a model with a texture and assigned shader.
 *               This struct also handles storing and setting handlers from the graphics renderer.
 */

#include "GUI.h"
#include "Core.h"

namespace GameEngine
{
    void GUI::initialize()
    {
        m_inputHandler = getInputHandler();
        m_clickable = false;
        m_clicked = false;
    }

    void GUI::onDisplay()
    {
        if (m_clickable)
        {
            checkClickGUI();
        }
        // RENDER QUAD WITH QUAD RENDERER
    }

    void GUI::checkClickGUI()
    {
        if (m_inputHandler.lock()->isMouseDown(MouseButton::Left))
        {
            if (rectIntersect())
            {
                m_clicked = true;
                return;
            }
        }
        m_clicked = false;
    }

    bool GUI::rectIntersect()
    {
        glm::vec3 GUIPos = getEntityTransform().lock()->getPosition();
        glm::vec2 mousePos = glm::vec2(m_inputHandler.lock()->getMousePos());
        mousePos.y = getWindowFromCore().lock()->m_windowHeight - mousePos.y; // Flip mouse pos into GUI space

        float halfWidth = getEntityTransform().lock()->getScale().x / 2.0f;
        float halfHeight = getEntityTransform().lock()->getScale().y / 2.0f;

        // X INTERSECTION
        if (GUIPos.x > mousePos.x)
        {
            if (mousePos.x < GUIPos.x - halfWidth)
            {
                return false;
            }
        }
        else
        {
            if (GUIPos.x + halfWidth < mousePos.x)
            {
                return false;
            }
        }

        // Y INTERSECTION
        if (GUIPos.y > mousePos.y)
        {
            if (mousePos.y < GUIPos.y - halfHeight)
            {
                return false;
            }
        }
        else
        {
            if (GUIPos.y + halfHeight < mousePos.y)
            {
                return false;
            }
        }

        return true;
    }
}