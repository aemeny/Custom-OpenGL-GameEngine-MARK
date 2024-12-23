/*
 *  File: Camera.cpp
 *  Author: Alex Emeny
 *  Date: December 6th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Camera.h
 *               It implements the functions for initializing the Camera variables,
 */

#include "Camera.h"
#include "Core.h"

#include <stdexcept>

namespace GameEngine
{
    void Camera::initialize(CameraProjection _projectionType, std::weak_ptr<Camera> _selfPtr, std::optional<PerspectiveParamaters> _perspectibeParams = std::nullopt)
    {
        m_self = _selfPtr;
        m_cameraProjection = _projectionType;

        m_transform = getEntityTransform();

        if (_projectionType == CameraProjection::Perspective)
        {
            if (_perspectibeParams.has_value() == false)
            {
                throw std::invalid_argument("Perspective projection camera requires Parameters (FOV, Near Plane, Far Plane).");
            }

            std::weak_ptr<Window> windowContext = getWindowFromCore();
            m_projectionMatrix = glm::perspective(glm::radians(_perspectibeParams->FOV),
                (float)(windowContext.lock()->m_windowWidth / windowContext.lock()->m_windowHeight),
                _perspectibeParams->nearPlane, _perspectibeParams->farPlane);

            /* Default viewing matrix set for camera */
            m_viewingMatrix = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if(_projectionType == CameraProjection::Orthographic)
        {
            if (_perspectibeParams.has_value() == true)
            {
                throw std::invalid_argument("Orthographic projection camera does not use perspective parameters.");
            }

            std::weak_ptr<Window> windowContext = getWindowFromCore();
            m_projectionMatrix = glm::ortho(0.0f, (float)windowContext.lock()->m_windowWidth, //Camera width bounds
                                            0.0f, (float)windowContext.lock()->m_windowHeight, //Camera height bounds
                                            -1.0f, 1.0f); // Far/Near plane
        }
    }

    void Camera::onLateTick()
    {
        if (m_cameraProjection == CameraProjection::Perspective)
        {
            updateViewingMatrix();
        }
    }

    void Camera::updateViewingMatrix()
    {
        if (m_transform.expired())
            return;

        /* Grab position and rotation */
        glm::vec3 position = m_transform.lock()->getPosition();
        glm::vec3 rotation = m_transform.lock()->getRotation();


        /* Calculate forwards direction */
        float yaw = glm::radians(rotation.y);
        float pitch = glm::radians(rotation.x);

        glm::vec3 forward;
        forward.x = cos(pitch) * cos(yaw);
        forward.y = sin(pitch);
        forward.z = cos(pitch) * sin(yaw);
        forward = glm::normalize(forward);


        /* Define up and right vectors */
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 target = position + forward;


        /* Update viewing matrix */
        m_viewingMatrix = glm::lookAt(position, target, up);
    }
}
