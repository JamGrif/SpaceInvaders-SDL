#pragma once

class ProgramClock
{
public:

	void init();
	void tick();

	int getDeltaTime() const { return m_deltaTime_ms; }
	int getFrameCount() const { return m_frameCountToDisplay; }
	int getLastFrame() const { return m_lastFrame_ms; }

	static ProgramClock* Instance() // Instance get
	{
		if (!s_pInstance)
			s_pInstance = new ProgramClock();
		return s_pInstance;
	}

private:
	ProgramClock();
	static ProgramClock* s_pInstance;

	int m_deltaTime_ms = 0;
	int m_lastFrame_ms = 0;

	int m_previousTime = 0;
	int m_frameCount = 0;
	int m_frameCountToDisplay = 0;
	int m_currentFrame = 0;

};
typedef ProgramClock TheProgramClock;
