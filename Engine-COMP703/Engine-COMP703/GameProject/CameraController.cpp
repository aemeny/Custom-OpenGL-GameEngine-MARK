/*
 *  File: CameraController.cpp
 *  Author: Alex Emeny
 *  Date: December 23rd, 2024 (Last Edited)
 *  Description: This file implements the methods declared in CameraController.h
 *               It implements the functions for camera movement around the world.
 */

#include "CameraController.h"

/// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///

void CameraController::initialize()
{
    /* Set mouse sensitivity*/
    m_mouseSensitivity = glm::vec2(0.2f);

    /* Grab engines input handler, lock mouse to center of screen and make it not visible */
    m_input = getInputHandler();
    m_input.lock()->setMouseRelativeMode(true);

    /* Get entities transform and set camera rotation to its */
    m_transform = getEntityTransform();
    m_cameraRotation = m_transform.lock()->getRotation();
}

void CameraController::onTick()
{
    /* Get mouse delta (movement since last frame) */
    glm::vec2 mouseDelta = m_input.lock()->getMouseDelta();

    /* Adjust rotation based on mouse movement */
    m_cameraRotation.y += mouseDelta.x * m_mouseSensitivity.x; // Yaw
    m_cameraRotation.x -= mouseDelta.y * m_mouseSensitivity.y; //Pitch

    /* Clamp pitch to avoid flipping camera */
    m_cameraRotation.x = glm::clamp(m_cameraRotation.x, -89.0f, 89.0f);

    m_transform.lock()->setRotation(m_cameraRotation);
}
