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


namespace GameEngine
{
    struct Camera : Component
    {
        void initialize(CameraProjection _projectionType, std::optional<PerspectiveParamaters> _perspectibeParams) override;
        
        glm::mat4 getProjectionMatrix() { return m_projectionMatrix; }
        glm::mat4 getViewingMatrix() { return m_viewingMatrix; } // MAKE USE OF ----------------
    private:
        CameraProjection m_cameraProjection;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewingMatrix;
    };
}