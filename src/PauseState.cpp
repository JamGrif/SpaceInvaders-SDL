#include "pch.h"
#include "PauseState.h"

#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "TextureManager.h"
#include "MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	for (auto o : m_gameObjects)
	{
		o->update();
	}
}

void PauseState::render()
{
	for (auto o : m_gameObjects)
	{
		o->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load("res/sprites/resume.png", "resumebutton"))
		return false;

	if (!TheTextureManager::Instance()->load("res/sprites/main.png", "mainbutton"))
		return false;

	GameObject* button1 = new MenuButton(new LoaderParams(200, 100, 200, 80, "mainbutton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumebutton"), s_resumePlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering PuaseState" << std::endl;
	return true;
}

bool PauseState::onExit()
{
	for (auto o : m_gameObjects)
	{
		o->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

	// Reset the mouse button states to false
	//TheInputHandler::Instance()->reset();

	std::cout << "Exiting PauseState" << std::endl;
	return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}


