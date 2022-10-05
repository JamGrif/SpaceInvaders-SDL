#pragma once
#include "BaseState.h"

//class GameObject;
//class Level;

class MainMenuState :
    public BaseState
{
public:
	virtual bool onEnterState() override;
	virtual bool onExitState() override;

	virtual void updateState() override;
	virtual void renderState() override;

	virtual std::string getStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

	// callback functions for menu items
	static void s_menuToPlay(); // Static as the functionality will only support static functions. Bit more complicated to handle regular member functions as function pointers.
	static void s_exitFromMenu();
};

