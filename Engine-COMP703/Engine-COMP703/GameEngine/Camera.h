/*
 *  File: Camera.h
 *  Author: Alex Emeny
 *  Date: December 6th, 2024 (Last Edited)
 *  Description: This file contains the Camera struct & related enums and structs,
 *               It defines functions for initializing perspective and orthographic cameras.
 *               This struct handles returning vital matrices for both 3/2D.
 */

#pragma once
#include "CameraTypes.h"
#include "Component.h"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

namespace GameEngine
{
    struct FrustumPlane
    {
        glm::vec3 m_normal; // Normal vector of the plane.
        float m_distance; // The distance measured from the Plane to the origin, along the Plane's normal.
    };

    struct Core;
    struct Transform;
    struct Camera : Component
    {
        void initialize(CameraProjection _projectionType, std::weak_ptr<Camera> _selfPtr, std::optional<PerspectiveParamaters> _perspectibeParams) override;
        void onLateTick() override;

        glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }
        void setProjectionMatrix(float _FOV, float _width, float _height, float _near, float _far);
        glm::mat4 getViewingMatrix() const { return m_viewingMatrix; }

        std::array<FrustumPlane, 6> getFrustumPlanes() const;
    
        /* Sets main camera in core as passed camera pointer */
        void setCameraAsMain() { setCameraAsMainProt(m_self); }

        void setShouldRender(bool _render) { m_shouldRender = _render; }
        bool getShouldRender() const { return m_shouldRender; }
    private:
        /* Updates the viewing matrix based on the entities transform */
        void updateViewingMatrix();

        /* Contains type Perspective or Orthographic */
        CameraProjection m_cameraProjection;

        /* Weak pointer to itself when needed to be passed */
        std::weak_ptr<Camera> m_self;

        /* Weak pointer to its transform set in the entity */
        std::weak_ptr<Transform> m_transform;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewingMatrix;

        /* If the camera should render to the main screen */
        bool m_shouldRender;
    };
}