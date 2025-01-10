/*
 *  File: GUI.h
 *  Author: Alex Emeny
 *  Date: January 10th, 2025 (Last Edited)
 *  Description: This file contains the GUI struct,
 *               It defines the function for displaying a GUI element with a given texture.
 *               This struct also handles storing the quad renderer for this GUI.
 */


#pragma once

#include "Component.h"
#include "TextureResource.h"
#include "ShaderResource.h"
#include "Input.h"

namespace GameEngine
{
    struct QuadRenderer;
    struct GUI : Component
    {
        void initialize() override;
        void onDisplay() override;

        void setClickable(bool _clickable) { m_clickable = _clickable; }

        bool hasBeenClicked() { return m_clicked; }

    private:
        /* Checks if the mouse click input happened over this GUI for interaction */
        void checkClickGUI();

        /* Checks the mouse position compared to the GUI position and scale */
        bool rectIntersect();

        bool m_clickable;
        std::weak_ptr<QuadRenderer> m_quadRenderer;

        /* Used to poll for clicks */
        std::weak_ptr<InputHandler> m_inputHandler;

        /* If this GUI element has been clicked this frame */
        bool m_clicked;
    };
}
