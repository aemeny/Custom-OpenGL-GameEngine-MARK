/*
 *  File: CameraController.h
 *  Author: Alex Emeny
 *  Date: December 23rd, 2024 (Last Edited)
 *  Description: This file contains the CameraController struct,
 *               It defines functions for camera movement around the world
 */

 /// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///

#pragma once
#include "../GameEngine/Component.h"
#include "../GameEngine/Transform.h"

struct CameraController : Component
{
    void initialize() override;
    void onTick() override;

    std::weak_ptr<Transform> m_playerCharacter;
private:
    /* Weak ref to the input handler */
    std::weak_ptr<InputHandler> m_input;

    /* Weak ref to the entities transform component */
    std::weak_ptr<Transform> m_transform;

    /* Sensitivity for mouse movement */
    glm::vec2 m_mouseSensitivity;

    /* Current camera rotation */
    glm::vec3 m_cameraRotation;

    /* Camera/Player movement multiplier */
    float m_movementSpeed;
};