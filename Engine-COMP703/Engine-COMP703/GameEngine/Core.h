#pragma once
#include "Window.h"
#include "Input.h"

namespace GameEngine
{
	struct Core
	{
		static std::shared_ptr<Core> initialize();

		void run();

	private:
		std::shared_ptr<InputHandler> inputHandler;
		std::shared_ptr<Window> windowContext;
	};
}