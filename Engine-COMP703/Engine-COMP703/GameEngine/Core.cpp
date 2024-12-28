/*
 *  File: Core.cpp
 *  Author: Alex Emeny
 *  Date: December 19th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Core.h.
 *               It implements the functions for initializing the Core variables, GLEW and SDL2.
 *				 It also takes care of the main game loop which is vital for the program to run.
 */

#include "Core.h"
#include <iostream>

namespace GameEngine
{
	/* Initializes essential libraries for the engine to run */
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		/* SDL Initialize */
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			/* Major fault: SDL_Init failed */
			throw std::runtime_error("Failed to initialize SDL");
		}

		/* SDL Window Initialize */
		int windowWidth = 800;
		int windowHeight = 800;
		rtn->m_windowContext = std::make_shared<Window>();
		rtn->m_windowContext->initialize(windowWidth, windowHeight);

		/* GLEW Initialize */
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Major fault: glewInit failed */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		/* Object variables Initialize */
		rtn->m_inputHandler = std::make_shared<InputHandler>(rtn->m_windowContext);
		rtn->m_environment = std::make_shared<Environment>();
		rtn->m_resources = std::make_shared<Resources>();
		rtn->m_lineRenderer = std::make_shared<LineRenderer>(rtn);
		rtn->m_physicsCore = std::make_shared<PhysicsSystem::PhysicsCore>();

		/* weak reference to its self to pass to its modules */
		rtn->m_self = rtn;

		/* Ensures the engine always has a module to build upon by default */
		rtn->addModule()->m_name = "Default";

		/* Returns core object to main() */
		return rtn;
	}

	/* Main engine game loop ticks all required engine components */
	void Core::run()
	{
		isGameRunning = true;

		/* Physics time steps */
		const double fixedTimeStep = 0.02; // 20 ms
		double physicsTimeAccumulator = 0.0;

		/* FPS tracker */
		int tickCount = 0;
		double DTCount = 0;

		while (isGameRunning)
		{
			/* Clear depth buffer */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/* Draw background */
			glClearColor(0.42f, 0.5f, 0.68f, 1.0f);


			/* Tick environment for delta time */
			m_environment->tickDeltaTime();
			tickCount++;
			DTCount += m_environment->getDeltaTime();
			physicsTimeAccumulator += m_environment->getDeltaTime();

			/* InputHandler tick, polls SDL for inputs */
			m_inputHandler->tick();


			/* Entity tick */
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				if (m_modules.at(mi)->getActiveStatus())
				{
					m_modules.at(mi)->tick();
				}
			}


			/* Physics tick */
			while (physicsTimeAccumulator >= fixedTimeStep)
			{
				m_environment->tickPhysicsDeltaTime();

				m_physicsCore->physicsTick();

				physicsTimeAccumulator -= fixedTimeStep;
			}


			/* Entity late tick */
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				if (m_modules.at(mi)->getActiveStatus())
				{
					m_modules.at(mi)->lateTick();
				}
			}


			/* Entity render */
			for (size_t ci = 0; ci < m_cameras.size(); ++ci)
			{
				/* Only render with the camera if th entity it is within is active */
				if (m_cameras.at(ci).lock()->m_entity.lock()->getActiveStatus())
				{
					m_activeRenderingCamera = m_cameras.at(ci);
					for (size_t mi = 0; mi < m_modules.size(); ++mi)
					{
						if (m_modules.at(mi)->getActiveStatus())
						{
							m_modules.at(mi)->render();
						}
					}
				}
			}

			/* Debug Lines Render */
			m_lineRenderer->renderDebugLines(m_self);

			/* GUI render */
			m_activeRenderingCamera = m_mainCamera; // Only main camera renders GUI
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				if (m_modules.at(mi)->getActiveStatus())
				{
					m_modules.at(mi)->GUIRender();
				}
			}


			/* Built in escape method from window */
			if (m_inputHandler->isKeyPressed(SDLK_ESCAPE))
				isGameRunning = false;


			/* Clear frame dependent input */
			m_inputHandler->clear();


			/* Swap window */
			SDL_GL_SwapWindow(m_windowContext->m_window);

			if (DTCount >= 1.0)
			{
				std::cout << tickCount << std::endl;

				DTCount -= 1.0;
				tickCount = 0;
			}
		}
	}

	/* Creates a new module, adds them to the core vector and returns for user use */
	std::shared_ptr<Module> Core::addModule()
	{
		std::shared_ptr<Module> rtn = std::make_shared<Module>();

		rtn->m_corePtr = m_self;
		rtn->m_self = rtn;
		rtn->m_active = true;

		/* Adds created module to vector storage in core */
		m_modules.push_back(rtn);

		/* Returns created module for user referencing and use */
		return rtn;
	}

	std::shared_ptr<Module> Core::getModule(std::string _name)
	{
		for (int mi = 0; mi < m_modules.size(); ++mi)
		{
			if (m_modules.at(mi)->m_name == _name)
			{
				return m_modules.at(mi);
			}
		}
		fprintf(stderr, "Error: No Module found with given name\n");
		return NULL;
	}

	std::shared_ptr<Module> Core::getModule(int _index)
	{
		if (_index < m_modules.size())
			return m_modules.at(_index);
		
		fprintf(stderr, "Error: No Module found within index range\n");
		return NULL;
	}
}