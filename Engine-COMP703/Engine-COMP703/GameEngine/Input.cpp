/*
 * File: Input.cpp
 * Author: Alex Emeny
 * Date: November 21th, 2024 (Last Edited)
 * Description: This file implements the methods declared in Input.h.
 *              It implements the functions for initializing the InputHandler variables and checking input.
 *				It also takes care of ticking SDL poll events to assign taken inputs.
 */

#include "Input.h"
#include "Window.h"

#include <iostream>

namespace GameEngine
{
	/* Input constructor, assigns a weak core ref and sets up InputHandler variables */
	InputHandler::InputHandler(std::weak_ptr<Window> _windowRef) :
		m_windowRef(_windowRef), m_keys(), m_pressedKeys(), m_releasedKeys(),
		m_mouseDown{false}, m_mouseDownHeld{false}, 
		m_mouseDelta(glm::vec2(0)), m_mousePos(glm::ivec2(0)),
		m_mouseLock(false), m_controller(NULL)
	{
		/* Initialize controller support */
		if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
			throw std::runtime_error("Failed to initialize SDL Controller Support");

		/* Loop through all joysticks found and if one is a controller assign to variable */
		for (size_t i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i)) 
			{
				m_controller = SDL_GameControllerOpen(i); 
				break;
			}
		}
	}

	/* Cleans up controller pointers */
	InputHandler::~InputHandler()
	{
		if (m_controller != NULL)
		{
			SDL_GameControllerClose(m_controller);
		}
		m_controller = nullptr;
	}

	/* Clears one frame valid inputs */
	void InputHandler::clear()
	{
		m_pressedKeys.clear();
		m_releasedKeys.clear();
		m_mouseDown = { false, false , false };
	}

/*  ----------------------------------------------------------------- */
/*  Region of functions that return true if a checked Input is active */
/*  ----------------------------------------------------------------- */
#pragma region Input Check Functions

	/* returns if a key is currently being held down */
	bool InputHandler::isKeyHeld(int _key)
	{
		for (int key : m_keys)
		{
			if (_key == key) {
				return true;
			}
		}
		return false;
	}
	/* returns if a key has been pressed this frame */
	bool InputHandler::isKeyPressed(int _key)
	{
		for (int key : m_pressedKeys)
		{
			if (_key == key) {
				return true;
			}
		}
		return false;
	}
	/* returns if a key has been released this frame */
	bool InputHandler::isKeyReleased(int _key)
	{
		for (int key : m_releasedKeys)
		{
			if (_key == key) {
				return true;
			}
		}
		return false;
	}
	/* returns if a mouse button has been clicked this frame */
	bool InputHandler::isMouseDown(MouseButton _button)
	{
		try
		{
			return m_mouseDown.at(static_cast<size_t>(_button));
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Invalid mouse button: " << static_cast<int>(_button) << std::endl;
			return false;
		}
	}
	/* returns if a mouse button is currently held down */
	bool InputHandler::isMouseDownHeld(MouseButton _button)
	{
		try
		{
			return m_mouseDownHeld.at(static_cast<size_t>(_button));
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Invalid mouse button: " << static_cast<int>(_button) << std::endl;
			return false;
		}
	}

#pragma endregion


	/* Checks all SDL poll events to check for mouse and keyboard input */
	void InputHandler::tick()
	{
		/* Reset mouse delta(velocity) each frame */
		m_mouseDelta.x = 0;
		m_mouseDelta.y = 0;

		/* Sets current mouse position */
		SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);

		/* Poll input events and loop through them */
		while (SDL_PollEvent(&m_event) != 0)
		{
			/* Check for any mouse movement */
			if (m_event.type == SDL_MOUSEMOTION) 
			{
				m_mouseDelta.x += m_event.motion.xrel;
				m_mouseDelta.y += m_event.motion.yrel;
			}
			/* Check if any keys have been pressed down */
			else if (m_event.type == SDL_KEYDOWN) 
			{
				int keyDown = m_event.key.keysym.sym;

				/* Add key pressed to pressed keys this frame */
				m_pressedKeys.push_back(keyDown);

				/* Check if key is already in held keys */
				bool check = true;
				for (int key : m_keys)
				{
					if (keyDown == key) {
						check = false;
					}
				}
				if (check)
				{
					/* Add non - duplicate key to held keys */
					m_keys.push_back(keyDown);
				}
			}
			/* Check if any keys have been released */
			else if (m_event.type == SDL_KEYUP)
			{
				int releasedKey = m_event.key.keysym.sym;

				/* Add key released to released keys this frame */
				m_releasedKeys.push_back(releasedKey);

				/* Remove released key from held keys list */
				std::vector<int>::iterator keyPosition = std::find(m_keys.begin(), m_keys.end(), releasedKey); // Find key in list
				/* If returned myVector.end() the element was not found */
				if (keyPosition != m_keys.end()) 
				{ 
					m_keys.erase(keyPosition);
				}
			}
			/* Check for mouse button down input */
			else if (m_event.type == SDL_MOUSEBUTTONDOWN) 
			{
				if (m_event.button.button == SDL_BUTTON_LEFT) {
					m_mouseDown.at(0) = m_mouseDownHeld.at(0) = true;
				}
				else if (m_event.button.button == SDL_BUTTON_RIGHT) {
					m_mouseDown.at(1) = m_mouseDownHeld.at(1) = true;
				}
				else if (m_event.button.button == SDL_BUTTON_MIDDLE) {
					m_mouseDown.at(2) = m_mouseDownHeld.at(2) = true;
				}
			}
			/* Check if a mouse button has been release */
			else if (m_event.type == SDL_MOUSEBUTTONUP)
			{
				if (m_event.button.button == SDL_BUTTON_LEFT) {
					m_mouseDownHeld.at(0) = false;
				}
				else if (m_event.button.button == SDL_BUTTON_RIGHT) {
					m_mouseDownHeld.at(1) = false;
				}
				else if (m_event.button.button == SDL_BUTTON_MIDDLE) {
					m_mouseDownHeld.at(2) = false;
				}
			}
			/* Check if controller input has been detected */
			/* Check for controller button down input */
			else if (m_event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				int keyDown = m_event.cbutton.button;

				/* Add key pressed to pressed keys this frame */
				m_pressedKeys.push_back(keyDown);

				/* Check if key is already in held keys */
				bool check = true;
				for (int key : m_keys)
				{
					if (keyDown == key) {
						check = false;
					}
				}
				if (check)
				{
					/* Add non - duplicate key to held keys */
					m_keys.push_back(keyDown);
				}
			}
			/* Check for controller button up input */
			else if (m_event.type == SDL_CONTROLLERBUTTONUP)
			{
				int releasedKey = m_event.cbutton.button;

				/* Add key released to released keys this frame */
				m_releasedKeys.push_back(releasedKey);

				/* Remove released key from held keys list */
				std::vector<int>::iterator keyPosition = std::find(m_keys.begin(), m_keys.end(), releasedKey); // Find key in list
				/* If returned myVector.end() the element was not found */
				if (keyPosition != m_keys.end())
				{
					m_keys.erase(keyPosition);
				}
			}
			/* Joystick motion */
			else if (m_event.type == SDL_JOYAXISMOTION)
			{
				/* X axis motion */
				if (m_event.jaxis.axis == 0) 
				{
					/* SIMPLE JOYSTICK MAPPING WITHOUT VECTORS */
					if (m_event.jaxis.value < -JOYSTICK_DEAD_ZONE_LEFT) // Left of dead zone
					{
						m_keys.push_back(SDLK_a);
					}
					else
					{
						/* Remove released key from held keys list */
						std::vector<int>::iterator position = std::find(m_keys.begin(), m_keys.end(), SDLK_a); //find key in list
						/* If returned myVector.end() the element was not found */
						if (position != m_keys.end())
						{
							m_keys.erase(position);
						}
					}

					if (m_event.jaxis.value > JOYSTICK_DEAD_ZONE_LEFT) // Right of dead zone
					{
						m_keys.push_back(SDLK_d);
					}
					else
					{
						/* Remove released key from held keys list */
						std::vector<int>::iterator position = std::find(m_keys.begin(), m_keys.end(), SDLK_d); //find key in list
						/* If returned myVector.end() the element was not found */
						if (position != m_keys.end())
						{
							m_keys.erase(position);
						}
					}
				}
				/* Y axis motion */
				else if (m_event.jaxis.axis == 1)
				{
					/* Left joystick handling */

					/* SIMPLE JOYSTICK MAPPING WITHOUT VECTORS */
					if (m_event.jaxis.value < -JOYSTICK_DEAD_ZONE_LEFT) // Below of dead zone
					{
						m_keys.push_back(SDLK_w);
					}
					else
					{
						/* Remove released key from held keys list */
						std::vector<int>::iterator position = std::find(m_keys.begin(), m_keys.end(), SDLK_w); //find key in list
						/* If returned myVector.end() the element was not found */
						if (position != m_keys.end())
						{
							m_keys.erase(position);
						}
					}

					if (m_event.jaxis.value > JOYSTICK_DEAD_ZONE_LEFT) // Above of dead zone
					{
						m_keys.push_back(SDLK_s);
					}
					else
					{
						/* Remove released key from held keys list */
						std::vector<int>::iterator position = std::find(m_keys.begin(), m_keys.end(), SDLK_s); //find key in list
						/* If returned myVector.end() the element was not found */
						if (position != m_keys.end())
						{
							m_keys.erase(position);
						}
					}
				}
			}
		}

		/* Handles right stick movement */
		if (m_controller != NULL)
		{
			SDL_Joystick* joystick = SDL_JoystickOpen(0);
			if (joystick)
			{
				/* Poll right joystick axes */
				Sint16 xAxis = SDL_JoystickGetAxis(joystick, 2);
				Sint16 yAxis = SDL_JoystickGetAxis(joystick, 3);

				/* Normalize and check outside dead zone */
				m_mouseDelta.x += (std::abs(xAxis) > JOYSTICK_DEAD_ZONE_RIGHT) ? xAxis / 32767.0f : 0.0f;
				m_mouseDelta.y += (std::abs(yAxis) > JOYSTICK_DEAD_ZONE_RIGHT) ? yAxis / 32767.0f : 0.0f;
			}
		}

		/* If mouse lock is true warp mouse to center of the screen after input is taken */
		if (m_mouseLock)
		{
			float halfWindowWidth = m_windowRef.lock()->m_windowWidth * 0.5f;
			float halfWindowHeight = m_windowRef.lock()->m_windowHeight * 0.5f; 
			SDL_WarpMouseInWindow(NULL, halfWindowWidth, halfWindowHeight);
		}
	}
}