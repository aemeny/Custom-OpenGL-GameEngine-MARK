#pragma once
#include "SDL2/SDL.h"

#include <memory>
#include <vector>

namespace GameEngine
{
	struct Core; 

	struct InputHandler
	{
		InputHandler(std::weak_ptr<Core> _coreRef);
		
		bool isKey(int _key); // Is the key being held down
		bool isKeyPressed(int _key); // Has the key been pressed this frame
		bool isKeyReleased(int _key); // Has the key been released this frame

		void checkInput();

	private:
		std::weak_ptr<Core> m_coreRef;

		SDL_Event m_event;

		// Keyboard input
		std::vector<int> m_keys;
		std::vector<int> m_pressedKeys;
		std::vector<int> m_releasedKeys;
	};
}