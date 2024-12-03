#pragma once
#include "glm/gtc/matrix_transform.hpp"

#include <optional>

namespace GameEngine
{
    enum class CameraProjection
    {
        Perspective,
        Orthographic
    };

    struct PerspectiveParamaters
    {
        float FOV;
        float nearPlane;
        float farPlane;
    };

    struct Camera 
    {
        Camera(CameraProjection _projectionType, std::optional<PerspectiveParamaters> _perspectibeParams); 
        // CHANGE TO INITIALIZE FOR COMPONENT ^^^^^^^^^^^^
        glm::mat4 getProjectionMatrix() { return m_projectionMatrix; }
        glm::mat4 getViewingMatrix() { return m_viewingMatrix; } // MAKE USE OF ----------------
    private:
        CameraProjection m_cameraProjection;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewingMatrix;
    };
}