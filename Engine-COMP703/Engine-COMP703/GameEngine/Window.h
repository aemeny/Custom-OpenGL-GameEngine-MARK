/*
 *  File: Window.h
 *  Author: Alex Emeny
 *  Date: November 15th, 2024
 *  Description: This file contains the Window struct,
 *               which is responsible for initializing the window and creating SDL Context.
 *               The Window struct also stores SDL window information / data.
 */

#pragma once
#include "../Graphics/GraphicsMasterHeader.h"

namespace GameEngine
{
	struct Window
	{
		/* Initializes SDL window and context with passed window height & width */
		void initialize(int _width, int _height);
		/* Deletes SDL Context and Destroyes Window. 
		   QUITS SDL PROGRAM */
		~Window();

		SDL_Window* m_window;
		SDL_GLContext m_context;

	private:
		int m_windowHeight, m_windowWidth;
	};
}