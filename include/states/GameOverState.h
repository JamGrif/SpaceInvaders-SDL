#pragma once
#include "MenuState.h"

class GameObject;

class GameOverState :
    public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
private:
	static const std::string s_gameOverID;

	static void s_gameOverToMain();
	static void s_restartPlay();

	std::vector <GameObject*> m_gameObjects;

};

