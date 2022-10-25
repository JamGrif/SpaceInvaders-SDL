#pragma once
#include "states/BaseState.h"

/// <summary>
/// The state used when the game is finished
/// </summary>
class GameOverState :
    public BaseState
{
public:
	virtual bool		onEnterState() override;
	virtual bool		onExitState() override;

	virtual void		updateState() override;
	virtual void		renderState() override;

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static const std::string s_gameOverID;

	static std::string	s_textCallback1();
	static std::string	s_textCallback2();

	static void			s_gameOverToMain();
	static void			s_restartPlay();
};

