/*
 *  File: Portal.cpp
 *  Author: Alex Emeny
 *  Date: January 5th, 2025 (Last Edited)
 *  Description: This file implements the methods declared in Portal.h
 *               It implements the functions for portal behavior within the world
 */

#include "Portal.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

 /// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///

void Portal::onTick()
{
    m_portalEntity.lock()->setActiveStatus(false);
    m_portalWall.lock()->setActiveStatus(false);
    m_characterEntity.lock()->setActiveStatus(true);

    /* Calculate relative position to portal */
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
    m_cameraTransform.lock()->setPosition(flippedPosition);


    /* Rotation */
    glm::vec3 rotPlayer = m_playerTransform.lock()->getRotation();
    rotPlayer.y -= 180;
    m_cameraTransform.lock()->setRotation(rotPlayer);
}

void Portal::onLateTick()
{
    m_portalEntity.lock()->setActiveStatus(true);
    m_portalWall.lock()->setActiveStatus(true);
    m_characterEntity.lock()->setActiveStatus(false);
}