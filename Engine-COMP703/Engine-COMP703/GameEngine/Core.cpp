#include "Core.h"

namespace GameEngine
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// SDL Initialise
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw std::runtime_error("Failed to initialize SDL");

		// SDL Window Initialise
		int windowWidth = 800;
		int windowHeight = 800;
		rtn->windowContext = std::make_shared<Window>();
		rtn->windowContext->initialize(windowWidth, windowHeight);

		// GLEW Initialise
		glewInit();

		// Object variables Initialise
		rtn->inputHandler = std::make_shared<InputHandler>(rtn);

		return rtn;
	}

	void Core::run()
	{
		while (true)
		{

		}
	}
}