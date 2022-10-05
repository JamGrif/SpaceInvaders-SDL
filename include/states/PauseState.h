#pragma once
#include "BaseState.h"

//class GameObject;
//class Level;

class PauseState :
    public BaseState
{
public:
	virtual bool onEnterState() override;
	virtual bool onExitState() override;

	virtual void updateState() override;
	virtual void renderState() override;

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static const std::string s_pauseID;

	// Callback functions
	static void s_pauseToMain();
	static void s_resumePlay();
};

