#pragma once
#include "MenuState.h"

class GameObject;

class PauseState :
    public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:

	// Callback functions
	static void s_pauseToMain();
	static void s_resumePlay();

	static const std::string s_pauseID;

	std::vector<GameObject*> m_gameObjects;
};

