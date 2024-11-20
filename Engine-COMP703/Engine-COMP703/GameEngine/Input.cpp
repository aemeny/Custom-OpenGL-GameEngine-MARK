#include "Input.h"

namespace GameEngine
{
	InputHandler::InputHandler(std::weak_ptr<Core> _coreRef) : m_coreRef(_coreRef) 
	{}

	bool InputHandler::isKey(int _key)
	{
		return false;
	}

	bool InputHandler::isKeyPressed(int _key)
	{
		return false;
	}

	bool InputHandler::isKeyReleased(int _key)
	{
		return false;
	}

	void InputHandler::checkInput()
	{
		while (SDL_PollEvent(&m_event) != 0)
		{
			if (m_event.type == SDL_MOUSEMOTION) // Check for any mouse movement
			{
				
			}
			else if (m_event.type == SDL_KEYDOWN) // Check if any keys have been pressed down
			{

			}
			else if (m_event.type == SDL_KEYUP) // Check if any keys have been released
			{

			}
		}
	}
}