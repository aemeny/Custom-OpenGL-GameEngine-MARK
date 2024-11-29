/*
 * File: Window.cpp
 * Author: Alex Emeny
 * Date: November 15th, 2024
 * Description: This file implements the methods declared in Window.h.
 *              It defines the functions for initializing the window and creating SDL Context.
 *				Cleans up SDL with Deleting Context and Destroying Window to finally Quit SDL
 */

#include "Window.h"
#include <iostream>

namespace GameEngine
{
	/* Initializes SDL window and context with passed window height & width */
	void Window::initialize(int _width, int _height)
	{
		m_windowWidth = _width;
		m_windowHeight = _height;

		if (!(m_window = SDL_CreateWindow("WINDOW",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			m_windowWidth, m_windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		{
			SDL_Quit();
			throw std::runtime_error("Failed to create Window");
		}

		if (!(m_context = SDL_GL_CreateContext(m_window)))
		{
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			throw std::runtime_error("Failed to create OpenGL context");
		}
	}

	/* Deletes SDL Context and Destroys Window.
		   QUITS SDL PROGRAM */
	Window::~Window()
	{
		if (m_context)
		{
			std::cout << "SDL_GL_DeleteContext \n" << std::endl;
			SDL_GL_DeleteContext(m_context);
		}
		if (m_window)
		{
			std::cout << "SDL_DestroyWindow \n" << std::endl;
			SDL_DestroyWindow(m_window);

			std::cout << "SDL_Quit \n" << std::endl;
			SDL_Quit();
		}
	}
}