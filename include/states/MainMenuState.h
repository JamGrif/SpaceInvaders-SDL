#pragma once
#include "states/BaseState.h"


/// <summary>
/// The state when game is first launched
/// </summary>
class MainMenuState :
    public BaseState
{
public:
	virtual bool		onEnterState() override;
	virtual bool		onExitState() override;

	virtual void		updateState() override;
	virtual void		renderState() override;

	virtual std::string getStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

	static void			s_menuToPlay();
	static void			s_exitFromMenu();
	static void			s_toggleSound();
	static void			s_toggleMusic();

	static bool			s_checkboxState1();
	static bool			s_checkboxState2();
};

