#include "Camera.h"

#include <stdexcept>

namespace GameEngine
{
    Camera::Camera(CameraProjection _projectionType, std::optional<PerspectiveParamaters> _perspectibeParams = std::nullopt)
    {
        m_cameraProjection = _projectionType;

        if (_projectionType == CameraProjection::Perspective)
        {
            if (_perspectibeParams.has_value() == false)
            {
                throw std::invalid_argument("Perspective projection camera requires Parameters (FOV, Near Plane, Far Plane).");
            }

            m_projectionMatrix = glm::perspective(glm::radians(_perspectibeParams->FOV),
                (float)(/*WINDOW WIDTH / WINDW HEIGHT*/ 800.0f / 800.0f),
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

            // ADD REFERENCE TO WINDOW HEIGHT / WIDH FROM CORE
            m_projectionMatrix = glm::ortho(0.0f, /*(float)WINDOW WIDTH*/ 800.0f, //Camera width bounds
                                            0.0f, /*(float)WINDOW HEIGHT*/800.0f, //Camera height bounds
                                            -1.0f, 1.0f); // Far/Near plane
        }
    }
}
