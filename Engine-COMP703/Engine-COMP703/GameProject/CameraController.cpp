/*
 *  File: CameraController.cpp
 *  Author: Alex Emeny
 *  Date: December 23rd, 2024 (Last Edited)
 *  Description: This file implements the methods declared in CameraController.h
 *               It implements the functions for camera movement around the world.
 */

#include "CameraController.h"
#include <iostream>

/// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///

void CameraController::initialize()
{
    m_mouseSensitivity = glm::vec2(0.1f);

    m_movementSpeed = 10.0f;
    m_canJump = true;
    m_intractable = true;

    /* Grab engines input handler, lock mouse to center of screen and make it not visible */
    m_input = getInputHandler();
    m_input.lock()->setMouseRelativeMode(true);

    /* Get entities transform and set camera rotation to its */
    m_transform = getEntityTransform();
    m_cameraRotation = m_transform.lock()->getRotation();
}

void CameraController::onTick()
{
    if (m_intractable)
    {
        /* CAMERA ROTATION */

        /* Get mouse delta (movement since last frame) */
        glm::vec2 mouseDelta = m_input.lock()->getMouseDelta();
        m_cameraRotation = m_transform.lock()->getRotation();

        /* Adjust rotation based on mouse movement */
        m_cameraRotation.y += mouseDelta.x * m_mouseSensitivity.x; // Yaw
        m_cameraRotation.x -= mouseDelta.y * m_mouseSensitivity.y; // Pitch

        /* Clamp pitch to avoid flipping the camera */
        m_cameraRotation.x = glm::clamp(m_cameraRotation.x, -89.0f, 89.0f);

        m_transform.lock()->setRotation(m_cameraRotation);


        /* CAMERA MOVEMENT */

        /* Calculate the forward vector based on camera's yaw */
        float yaw = glm::radians(m_cameraRotation.y);
        glm::vec3 forward = glm::vec3(cos(yaw), 0.0f, sin(yaw));
        forward = glm::normalize(forward); // Ensure the vector is of unit length

        /* Calculate the Right vector (for strafing) */
        glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));


        /* Apply movement to position */
        glm::vec3 position = m_transform.lock()->getPosition();
        glm::vec3 movement(0.0f);

        /* Add movement based on input */
        if (m_input.lock()->isKeyHeld(SDLK_w)) // Forward
        {
            movement += forward;
        }
        if (m_input.lock()->isKeyHeld(SDLK_s)) // Backward
        {
            movement -= forward;
        }
        if (m_input.lock()->isKeyHeld(SDLK_a)) // Strafe left
        {
            movement -= right;
        }
        if (m_input.lock()->isKeyHeld(SDLK_d)) // Strafe right
        {
            movement += right;
        }

        /* Normalize movement for consistency */
        if (glm::length(movement) > 0.0f)
        {
            movement = glm::normalize(movement);
        }

        /* Multiply movement by speed and delta time */
        position += movement * m_movementSpeed * getDTAsFloat();

        /* Apply new position to location */
        m_transform.lock()->setPosition(position);
        m_playerCharacter.lock()->setPosition(glm::vec3(position.x, position.y - 1.5f, position.z));
        m_playerCharacter.lock()->setRotation(glm::vec3(0.0f, -m_cameraRotation.y + 90.0f, 0.0f));
    }
}

void CameraController::sendToFirstLocation()
{
    /* Apply default position and rotation */
    glm::vec3 defaultPos = glm::vec3(13.0f, 3.1f, -19.5f);
    m_cameraRotation.x = 0.0f;
    m_cameraRotation.y = 90.0f;

    m_transform.lock()->setPosition(defaultPos);
    m_transform.lock()->setRotation(m_cameraRotation);
    m_playerCharacter.lock()->setPosition(glm::vec3(defaultPos.x, defaultPos.y - 1.5f, defaultPos.z));
    m_playerCharacter.lock()->setRotation(glm::vec3(0.0f, -m_cameraRotation.y + 90.0f, 0.0f));
}
