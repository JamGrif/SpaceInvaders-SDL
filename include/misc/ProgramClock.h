#pragma once

class ProgramClock
{
public:

	void init();
	void tick();

	double getDeltaTime() const { return m_deltaTime; }
	int getFrameCount() const { return m_frameCountToDisplay; }
	double getLastFrame() const { return m_lastFrame; }

	static ProgramClock* Instance() // Instance get
	{
		if (!s_pInstance)
			s_pInstance = new ProgramClock();
		return s_pInstance;
	}

private:
	ProgramClock();
	static ProgramClock* s_pInstance;

	double m_deltaTime = 0;
	double m_lastFrame = 0;

	double m_previousTime = 0;
	int m_frameCount = 0;
	int m_frameCountToDisplay = 0;
	double m_currentFrame = 0;

};
typedef ProgramClock TheProgramClock;
