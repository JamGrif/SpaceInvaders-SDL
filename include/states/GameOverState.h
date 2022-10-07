#pragma once
#include "BaseState.h"

class GameOverState :
    public BaseState
{
public:
	virtual bool onEnterState() override;
	virtual bool onExitState() override;

	virtual void updateState() override;
	virtual void renderState() override;

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static const std::string s_gameOverID;

	static void s_gameOverToMain();
	static void s_restartPlay();
};

