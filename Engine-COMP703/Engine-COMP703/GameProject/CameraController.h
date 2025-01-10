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
#include "../Physics/RigidBody.h"
#include "../Physics/BoxCollider.h"

struct CameraController : Component
{
    void initialize() override;
    void onTick() override;

    void sendToFirstLocation();

    std::weak_ptr<Transform> m_playerCharacter;
    std::weak_ptr<PhysicsSystem::RigidBody> m_rigidBody;
    std::weak_ptr<PhysicsSystem::AABBCollider> m_boxCollider;

    /* If the controller should be intractable */
    bool m_intractable;
private:
    /* Is can jump again after collision check */
    bool m_canJump;

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