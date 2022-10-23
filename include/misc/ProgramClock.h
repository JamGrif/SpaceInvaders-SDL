#pragma once

/// <summary>
/// Clock that gets ticked at the start of every frame
/// Calculates the delta time
/// </summary>
class ProgramClock
{
public:
	void init();
	void tick();

	// Get time to create previous frame in milliseconds
	uint32_t getDeltaTime_ms() const { return m_deltaTime_ms; }

	static ProgramClock* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new ProgramClock();
		return s_pInstance;
	}

private:
	static ProgramClock* s_pInstance;

	uint32_t m_deltaTime_ms;
	uint32_t m_currentFrame;
	uint32_t m_lastFrame_ms;

	// Time to delay each frame in order to stick to a specified FPS
	// Gives the amount of time we need to delay the game between loops to keep the frame rate constant. (1000 = number of milliseconds in a second)
	uint32_t m_delayTime;

	ProgramClock():m_deltaTime_ms(0), m_currentFrame(0), m_lastFrame_ms(0), m_delayTime(0) {}						// Prevent outside unwanted construction
	ProgramClock(const ProgramClock&) :m_deltaTime_ms(0), m_currentFrame(0), m_lastFrame_ms(0), m_delayTime(0) {}	// Prevent construction by copying
	ProgramClock& operator=(const ProgramClock&) {}																	// Prevent assignment
	~ProgramClock() {}																								// Prevent outside unwanted destruction
};
typedef ProgramClock TheProgramClock;
