#include "pch.h"
#include "misc/ProgramClock.h"

#include "SDL2/SDL.h"

#define FPS 60

ProgramClock* ProgramClock::s_pInstance = nullptr;

/// <summary>
/// Initializes the program clock
/// </summary>
void ProgramClock::init()
{
	m_delayTime = static_cast<int>(1000.0f / FPS);
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

	// If it is less than the time we want a frame to take, we call SDL_Delay to make the loop wait for the amount of time we want, subtracting how long the loop already took to complete
	if (m_deltaTime_ms < m_delayTime)
		SDL_Delay((int)(m_delayTime - m_deltaTime_ms));
}
