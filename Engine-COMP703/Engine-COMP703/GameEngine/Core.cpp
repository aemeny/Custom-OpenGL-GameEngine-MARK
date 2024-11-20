#include "Core.h"

namespace GameEngine
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		rtn->windowContext = std::make_shared<Window>();

		// Window Initialise
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("Failed to initialize SDL");
		}

		int windowWidth = 800;
		int windowHeight = 800;
		rtn->windowContext->initialize(windowWidth, windowHeight);

		return rtn;
	}

	void Core::run()
	{
		while (true)
		{

		}
	}
}