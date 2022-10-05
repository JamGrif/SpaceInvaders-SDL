#pragma once
class ProgramClock
{
public:

	void init();
	void tick();

	double getDeltaTime();
	int getFrameCount();

	static ProgramClock* Instance();
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
