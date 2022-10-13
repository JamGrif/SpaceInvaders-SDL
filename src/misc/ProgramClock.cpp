#include "pch.h"
#include "misc/ProgramClock.h"

#include "SDL2/SDL.h"

ProgramClock* ProgramClock::s_pInstance = nullptr;

/// <summary>
/// Initializes the program clock
/// </summary>
void ProgramClock::init()
{
}

/// <summary>
/// Tick the clock, updating the values for this frame
/// Called at the start of every frame
/// </summary>
void ProgramClock::tick()
{
	// Delta time
	m_currentFrame = SDL_GetTicks();
	m_deltaTime_ms = m_currentFrame - m_lastFrame_ms;
	m_lastFrame_ms = m_currentFrame;
}
