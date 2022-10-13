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
	int getDeltaTime_ms() const { return m_deltaTime_ms; }

	static ProgramClock* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new ProgramClock();
		return s_pInstance;
	}

private:
	static ProgramClock* s_pInstance;

	int m_deltaTime_ms;
	int m_currentFrame;
	int m_lastFrame_ms;

	ProgramClock():m_deltaTime_ms(0), m_currentFrame(0), m_lastFrame_ms(0) {}						// Prevent outside unwanted construction
	ProgramClock(const ProgramClock&) :m_deltaTime_ms(0), m_currentFrame(0), m_lastFrame_ms(0) {}	// Prevent construction by copying
	ProgramClock& operator=(const ProgramClock&) {}													// Prevent assignment
	~ProgramClock() {}																				// Prevent outside unwanted destruction
};
typedef ProgramClock TheProgramClock;
