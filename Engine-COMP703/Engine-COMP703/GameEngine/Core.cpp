#include "Core.h"

namespace GameEngine
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// SDL Initialize
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw std::runtime_error("Failed to initialize SDL");

		// SDL Window Initialize
		int windowWidth = 800;
		int windowHeight = 800;
		rtn->m_windowContext = std::make_shared<Window>();
		rtn->m_windowContext->initialize(windowWidth, windowHeight);

		// GLEW Initialize
		glewInit();

		// Object variables Initialize
		rtn->m_inputHandler = std::make_shared<InputHandler>(rtn->m_windowContext);
		rtn->m_environment = std::make_shared<Environment>();

		return rtn;
	}

	void Core::run()
	{
		isGameRunning = true;

		// TEMP MODEL LOADING FOR TESTING
		std::shared_ptr<GraphicsRenderer::ModelHandler> model =
			std::make_shared<GraphicsRenderer::ModelHandler>("../Samples/Models/Curuthers/Curuthers.obj");

		std::shared_ptr<GraphicsRenderer::ShaderHandler> shader =
			std::make_shared<GraphicsRenderer::ShaderHandler>("../Shaders/Perspective/VertexShader.txt", "../Shaders/Perspective/FragmentShader.txt");

		std::shared_ptr<GraphicsRenderer::TextureHandler> texture =
			std::make_shared<GraphicsRenderer::TextureHandler>("../Samples/Textures/Curuthers/Curuthers.png");

		glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)(900 / 900), 0.01f, 100.0f);


		while (isGameRunning)
		{
			//Clear depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//draw background
			glClearColor(0.42f, 0.5f, 0.68f, 1.0f);

			/* Tick environment for delta time */
			m_environment->tickDeltaTime();

			/* InputHandler tick, polls SDL for inputs */
			m_inputHandler->tick();

			/* Entity tick */

			/* GUI tick */

			/* Entity render */
			shader->bindShader(projection, "u_Projection");
			shader->renderModel(model, texture);

			/* GUI render */

			/* Escape method from window */
			if (m_inputHandler->isKeyPressed(SDLK_ESCAPE))
				isGameRunning = false;

			/* Clear frame dependent input */
			m_inputHandler->clear();

			/* Swap window */
			SDL_GL_SwapWindow(m_windowContext->m_window);
		}
	}
}