#pragma once
#include "states/BaseState.h"

/// <summary>
/// The state used when game is paused
/// </summary>
class PauseState :
    public BaseState
{
public:
	virtual bool		onEnterState() override;
	virtual bool		onExitState() override;

	virtual void		updateState() override;
	virtual void		renderState() override;

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static const std::string s_pauseID;

	static void			s_pauseToMain();
	static void			s_resumePlay();
};

