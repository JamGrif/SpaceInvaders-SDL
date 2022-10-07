#include "pch.h"
#include "misc/ProgramClock.h"

#include "SDL2/SDL.h"

ProgramClock* ProgramClock::s_pInstance = nullptr;

void ProgramClock::init()
{
	m_previousTime = SDL_GetTicks();
	m_frameCount = 0;
	m_currentFrame = 0;
}

void ProgramClock::tick()
{
	// Delta time
	m_currentFrame = SDL_GetTicks();
	m_deltaTime = m_currentFrame - m_lastFrame;
	m_lastFrame = m_currentFrame;

	// Calculate framecount
	m_frameCount++;

	// If a second has passed
	if (m_currentFrame - m_previousTime >= 1.0)
	{
		m_frameCountToDisplay = m_frameCount;
		m_frameCount = 0;
		m_previousTime = m_currentFrame;
	}
}

ProgramClock::ProgramClock()
{
}

