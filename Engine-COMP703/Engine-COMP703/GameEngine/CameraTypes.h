/*
 *  File: CameraTypes.h
 *  Author: Alex Emeny
 *  Date: December 6th, 2024
 *  Description: This file contains the CameraPorjection enum and PerspectiveParamaters struct,
 *               It defines types for both Perspective and Orthographic.
 *               This also contains a struct which holds necessary data for perspective based cameras.
 */
#pragma once

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
}