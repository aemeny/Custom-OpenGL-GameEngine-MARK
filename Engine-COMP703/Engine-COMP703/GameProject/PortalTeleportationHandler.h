/*
 *  File: PortalTeleportationHandler.h
 *  Author: Alex Emeny
 *  Date: January 7th, 2025 (Last Edited)
 *  Description: This file contains the PortalTeleportationHandler struct,
 *               It defines functions for portal teleportation behavior within the world
 */

 /// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///


#pragma once

#include "../GameEngine/Entity.h"
#include "../Physics/BoxCollider.h"

struct PortalTeleportationHandler : Component
{
    void initialize() override;
    void onLateTick() override;

    std::weak_ptr<Transform> m_playerTransform;
    std::weak_ptr<AABBCollider> m_playerCollider;
    std::weak_ptr<AABBCollider> m_portalCollider;
    std::weak_ptr<Transform> m_linkedPortalTransform;
private:
    bool m_dirty;
    std::weak_ptr<Transform> m_portalTransform;
};