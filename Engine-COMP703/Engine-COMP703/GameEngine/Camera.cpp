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
        m_shouldRender = true;

        m_transform = getEntityTransform();

        if (_projectionType == CameraProjection::Perspective)
        {
            if (_perspectibeParams.has_value() == false)
            {
                throw std::invalid_argument("Perspective projection camera requires Parameters (FOV, Near Plane, Far Plane).");
            }

            std::weak_ptr<Window> windowContext = getWindowFromCore();
            m_projectionMatrix = glm::perspective(glm::radians(_perspectibeParams->FOV),
                static_cast<float>(windowContext.lock()->m_windowWidth) / static_cast<float>(windowContext.lock()->m_windowHeight),
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

    void Camera::setProjectionMatrix(float _FOV, float _width, float _height, float _near, float _far)
    {
        m_projectionMatrix = glm::perspective(glm::radians(_FOV),
            _width / _height,
            _near, _far);
    }

    std::array<FrustumPlane, 6> Camera::getFrustumPlanes() const
    {
        std::array<FrustumPlane, 6> frustumePlanes;
        glm::mat4 viewProjection = getProjectionMatrix() * getViewingMatrix();

        /* Left Plane */
        frustumePlanes[0].m_normal = glm::vec3(viewProjection[0][3] + viewProjection[0][0],
                                               viewProjection[1][3] + viewProjection[1][0],
                                               viewProjection[2][3] + viewProjection[2][0]);
        frustumePlanes[0].m_distance = viewProjection[3][3] + viewProjection[3][0];

        /* Right Plane */
        frustumePlanes[1].m_normal = glm::vec3(viewProjection[0][3] - viewProjection[0][0],
                                               viewProjection[1][3] - viewProjection[1][0],
                                               viewProjection[2][3] - viewProjection[2][0]);
        frustumePlanes[1].m_distance = viewProjection[3][3] - viewProjection[3][0];

        /* Bottom Plane */
        frustumePlanes[2].m_normal = glm::vec3(viewProjection[0][3] + viewProjection[0][1],
                                               viewProjection[1][3] + viewProjection[1][1],
                                               viewProjection[2][3] + viewProjection[2][1]);
        frustumePlanes[2].m_distance = viewProjection[3][3] + viewProjection[3][1];

        /* Top Plane */
        frustumePlanes[3].m_normal = glm::vec3(viewProjection[0][3] - viewProjection[0][1],
                                               viewProjection[1][3] - viewProjection[1][1],
                                               viewProjection[2][3] - viewProjection[2][1]);
        frustumePlanes[3].m_distance = viewProjection[3][3] - viewProjection[3][1];

        // Near Plane
        frustumePlanes[4].m_normal = glm::vec3(viewProjection[0][3] + viewProjection[0][2],
            viewProjection[1][3] + viewProjection[1][2],
            viewProjection[2][3] + viewProjection[2][2]);
        frustumePlanes[4].m_distance = viewProjection[3][3] + viewProjection[3][2];

        // Far Plane
        frustumePlanes[5].m_normal = glm::vec3(viewProjection[0][3] - viewProjection[0][2],
            viewProjection[1][3] - viewProjection[1][2],
            viewProjection[2][3] - viewProjection[2][2]);
        frustumePlanes[5].m_distance = viewProjection[3][3] - viewProjection[3][2];

        /* Normalize the planes */
        for (auto& plane : frustumePlanes) {
            float length = glm::length(plane.m_normal);
            plane.m_normal /= length;
            plane.m_distance /= length;

            plane.m_normal = -plane.m_normal;
            plane.m_distance = -plane.m_distance;
        }

        return frustumePlanes;
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
