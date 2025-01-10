/*
 *  File: MenuManager.h
 *  Author: Alex Emeny
 *  Date: January 10th, 2025 (Last Edited)
 *  Description: This file contains the MenuManager struct,
 *               It defines functions for the menu and UI
 */

 /// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///


#pragma once

#include "../GameEngine/Component.h"
#include "../GameEngine/GUI.h"
#include "CameraController.h"

struct MenuManager : Component
{
    void initialize() override;
    void onLateTick() override;

    std::weak_ptr<GUI> m_playButton;
    std::weak_ptr<GUI> m_exitButton;
    std::weak_ptr<GUI> m_restartButton;

    std::weak_ptr<CameraController> m_camController;

    std::weak_ptr<AABBCollider> m_playerCollider;
    std::weak_ptr<AABBCollider> m_restatCollider;

    std::weak_ptr<Core> m_engineCore;

private:
    bool m_dirty;
    std::weak_ptr<InputHandler> m_input;
};