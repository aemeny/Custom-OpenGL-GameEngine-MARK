/*
 * File: Environment.cpp
 * Author: Alex Emeny
 * Date: November 27th, 2024
 * Description: This file implements the methods declared in Environment.h.
 *              It defines the functions for initializing delta time.
 *				Manages and updates delta time.
 */

#include "Environment.h"

#include <Windows.h>

namespace GameEngine
{
	/* Assigns values to default and calls for initialization */
	Environment::Environment() : m_deltaTime(0), m_last(0)
	{
		initialize();
	}

	/* Initializes last tick count as a start point before the first frame */
	void Environment::initialize()
	{
#ifdef _WIN32
		m_last = GetTickCount64();
#else
		struct timeval tv = { 0 };
		gettimeofday(&tv, NULL);
		last = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
#endif
	}
	
	/* Calls for Current tick count to compare from last frame to calculate deltaTime */
	void Environment::tickDeltaTime()
	{
#ifdef _WIN32
		DWORD curr = GetTickCount64();
#else
		struct timeval tv = { 0 };
		gettimeofday(&tv, NULL);
		double curr = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
#endif
		double diff = curr - m_last;
		m_deltaTime = diff / 1000.0f;
		m_last = curr;
	}

	/* returns deltaTime */
	double Environment::getDeltaTime() const
	{
		return m_deltaTime;
	}
}