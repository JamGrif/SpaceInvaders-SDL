#pragma once
#include "MenuState.h"

class GameObject;

class MainMenuState :
    public MenuState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	std::vector<GameObject*> m_gameObjects;

	// callback functions for menu items
	static void s_menuToPlay(); // Static as the functionality will only support static functions. Bit more complicated to handle regular member functions as function pointers.
	static void s_exitFromMenu();
};

