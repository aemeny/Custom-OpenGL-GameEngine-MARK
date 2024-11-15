#pragma once
#include "Window.h"

#include <memory>

namespace GameEngine
{
	struct Core
	{
		static std::shared_ptr<Core> initialize();

	private:
		std::shared_ptr<Window> windowContext;
	};
}