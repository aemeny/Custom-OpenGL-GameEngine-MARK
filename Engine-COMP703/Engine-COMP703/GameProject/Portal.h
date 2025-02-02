/*
 *  File: Portal.h
 *  Author: Alex Emeny
 *  Date: January 5th, 2025 (Last Edited)
 *  Description: This file contains the Portal struct,
 *               It defines functions for portal behavior within the world
 */

 /// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///


#pragma once
#include "../GameEngine/Entity.h"
#include "../GameEngine/Camera.h"
#include "../Physics/BoxCollider.h"

struct Portal : Component
{
    void onTick() override;
    void onLateTick() override;

    /* To activate/deactivate when rendering */
    std::weak_ptr<Entity> m_portalEntity;
    std::weak_ptr<Entity> m_portalWall;
    std::weak_ptr<Entity> m_characterEntity; 

    std::vector<std::weak_ptr<Entity>> m_portalBoarders;

    /* Optimization check for rendering */
    std::weak_ptr<Camera> m_renderingCam;
    std::weak_ptr<Camera> m_playerCam;
    std::weak_ptr<AABBCollider> m_portalCollider;

    /* For relative position math */
    std::weak_ptr<Transform> m_cameraTransform;
    std::weak_ptr<Transform> m_playerTransform;
    std::weak_ptr<Transform> m_portalTransform;
    std::weak_ptr<Transform> m_linkedPortalTransform;
};