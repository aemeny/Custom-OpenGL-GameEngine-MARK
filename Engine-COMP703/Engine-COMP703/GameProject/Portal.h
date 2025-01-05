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

struct Portal : Component
{
    void onTick() override;

    std::weak_ptr<Entity> m_portalEntity;
    std::weak_ptr<Transform> m_cameraTransform;
    std::weak_ptr<Transform> m_playerTransform;
};