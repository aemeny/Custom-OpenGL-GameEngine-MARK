#include "MenuManager.h"
#include "../GameEngine/Core.h"
#include <iostream>

void MenuManager::initialize()
{
    m_dirty = true;
    getInputHandler().lock()->setMouseRelativeMode(false);
}

void MenuManager::onLateTick()
{
    if (m_dirty)
    {
        m_dirty = false;
        m_playButton.lock()->setClickable(true);
        m_exitButton.lock()->setClickable(true);
        m_camController.lock()->m_intractable = false;
        m_restartButton.lock()->m_thisEntity.lock()->setActiveStatus(false);
    }

    if (m_playButton.lock()->hasBeenClicked())
    {
        m_playButton.lock()->m_thisEntity.lock()->setActiveStatus(false);
        m_exitButton.lock()->m_thisEntity.lock()->setActiveStatus(false);
        getInputHandler().lock()->setMouseRelativeMode(true);
        m_camController.lock()->m_intractable = true;
    }
    else if (m_exitButton.lock()->hasBeenClicked())
    {
        m_engineCore.lock()->stopProgram();
    }
}
