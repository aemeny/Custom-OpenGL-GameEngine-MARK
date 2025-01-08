/*
 *  File: PortalTeleportationHandler.cpp
 *  Author: Alex Emeny
 *  Date: January 7th, 2025 (Last Edited)
 *  Description: This file implements the methods declared in PortalTeleportationHandler.h
 *               It implements the functions for portal teleportation behavior within the world
 */

#include "PortalTeleportationHandler.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

void PortalTeleportationHandler::initialize()
{
    m_portalTransform = getEntityTransform();
    m_portalName = m_entity.lock()->m_name;
    m_dirty = true;
}

void PortalTeleportationHandler::onLateTick()
{
    glm::vec3 offsetFromPortal = m_playerTransform.lock()->getPosition() - m_portalTransform.lock()->getPosition();
    glm::vec3 forward = glm::normalize(glm::quat(glm::radians(m_playerTransform.lock()->getRotation())) * glm::vec3(0.0f, 0.0f, -1.0f));
    int portalSide = glm::sign(glm::dot(offsetFromPortal, forward));
    int portalSideOld = glm::sign(glm::dot(oldOffsetFromPortal, forward));

    if (portalSide != portalSideOld)
    {
        if (m_playerCollider.lock()->hasCollided() && m_playerCollider.lock()->ifCollidedWithName(m_portalName))
        {
            if (!m_dirty)
            {

                glm::mat4 portalLocalToWorld = m_portalTransform.lock()->getLocalToWorldMatrix();
                glm::mat4 linkedPortalWorldToLocal = glm::inverse(m_linkedPortalTransform.lock()->getLocalToWorldMatrix());
                glm::mat4 playerCameraLocalToWorld = m_playerTransform.lock()->getLocalToWorldMatrix();

                glm::mat4 m = portalLocalToWorld * linkedPortalWorldToLocal * playerCameraLocalToWorld;

                glm::vec3 position;
                glm::quat rotation;
                glm::vec3 scale, skew;
                glm::vec4 perspective;
                glm::decompose(m, scale, rotation, position, skew, perspective);

                /* Position */
                glm::vec3 relativePosition = position - m_portalTransform.lock()->getPosition();
                glm::vec3 flippedPosition = m_portalTransform.lock()->getPosition() - relativePosition;
                glm::vec3 posPlayer = m_playerTransform.lock()->getPosition();
                flippedPosition.y = posPlayer.y;
                flippedPosition.z -= 1.1f;
                m_playerTransform.lock()->setPosition(flippedPosition);

                /* Rotation */
                glm::vec3 rotPlayer = m_playerTransform.lock()->getRotation();
                rotPlayer.y -= 180;
                m_playerTransform.lock()->setRotation(rotPlayer);

                m_dirty = true;

            }
        }
        else if (m_dirty)
        {
            m_dirty = false;
        }
    }
    else
    {
        oldOffsetFromPortal = offsetFromPortal;
    }
}