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

            // TEMP VIEW MATRIX SET UP
            m_viewingMatrix = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Camera pos, Center, Up direction
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
}
