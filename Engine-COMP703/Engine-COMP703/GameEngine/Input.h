/*
 * File: Input.H
 * Author: Alex Emeny
 * Date: November 21th, 2024 (Last Edited)
 * Description: This file contains the InputHandler struct.
 *              It defines the functions for initializing the Input variables and checking input.
 *				This class handles holding data from the keyboard and mouse.
 */

#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <memory>
#include <vector>
#include <array>

namespace GameEngine
{
	struct Window;

	/* Enum that holds more meaningful reference to mouse input compared to an array index */
	enum class MouseButton
	{
		Left,   
		Right,  
		Middle
	};

	struct InputHandler
	{
		/* Input constructor, assigns a weak Window ref and sets up InputHandler variables */
		InputHandler(std::weak_ptr<Window> _coreRef);
		/* Cleans up controller pointers */
		~InputHandler();
		
		/* Returns if a key is currently being held down */
		bool isKeyHeld(int _key);
		/* Returns if a key has been pressed this frame */
		bool isKeyPressed(int _key);
		/* Returns if a key has been released this frame */
		bool isKeyReleased(int _key);

		/* Returns if a mouse button has been clicked this frame */
		bool isMouseDown(MouseButton _button);
		/* Returns if a mouse button is currently held down */
		bool isMouseDownHeld(MouseButton _button);
		/* Getter for mouse coordinate on the screen */
		glm::ivec2 getMousePos() const { return m_mousePos; } 
		/* Getter for the current velocity of the mouse for this frame */
		glm::vec2 getMouseDelta() const { return m_mouseDelta; }

		/* Checks all SDL poll events to check for mouse and keyboard input */
		void tick();
		/* Clears one frame valid inputs */
		void clear();

		/* If the mouse cursor should be shown */
		void setCursorActive(bool _active) { _active ? SDL_ShowCursor(SDL_ENABLE) : SDL_ShowCursor(SDL_DISABLE); }

		/* Setter for locking the mouse to the center of the screen */
		void setMouseLock(bool _lock) { m_mouseLock = _lock; }

		/* Sets the mouse cursor to relative mode, locking and setting invisible */
		void setMouseRelativeMode(bool _active) { _active ? SDL_SetRelativeMouseMode(SDL_TRUE) : SDL_SetRelativeMouseMode(SDL_FALSE); }

	private:
		/* Weak reference to window handler for updated window sizes */
		std::weak_ptr<Window> m_windowRef;

		/* SDL Events handler, used to poll events */
		SDL_Event m_event;

		/* Keyboard input */
		std::vector<int> m_keys;
		std::vector<int> m_pressedKeys;
		std::vector<int> m_releasedKeys;

		/* Mouse Input */
		glm::ivec2 m_mousePos;
		glm::vec2 m_mouseDelta;
		std::array<bool, 3> m_mouseDown;
		std::array<bool, 3> m_mouseDownHeld;

		/* If mouse should be locked to the middle of the screen */
		bool m_mouseLock;

		/* referenced code for controller SDL support
		*  https://lazyfoo.net/tutorials/SDL/19_gamepads_and_joysticks/index.php
		*/
		/* Controller Input */
		SDL_GameController* m_controller;
		const int JOYSTICK_DEAD_ZONE_LEFT = 28000; //Analog joystick dead zone
		const int JOYSTICK_DEAD_ZONE_RIGHT = 16000; 
	};
}