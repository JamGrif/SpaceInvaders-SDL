#include "pch.h"
#include "GameOverState.h"

#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update()
{
	for (auto o : m_gameObjects)
	{
		o->update();
	}
}

void GameOverState::render()
{
	for (auto o : m_gameObjects)
	{
		o->draw();
	}
}

bool GameOverState::onEnter()
{
	if (!TheTextureManager::Instance()->load("res/sprites/gameover.png", "gameovertext"))
		return false;

	if (!TheTextureManager::Instance()->load("res/sprites/main.png", "mainbutton"))
		return false;

	if (!TheTextureManager::Instance()->load("res/sprites/restart.png", "restartbutton"))
		return false;

	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext"), 2);
	GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering GameOverState" << std::endl;
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");

	std::cout << "Exiting GameOverState" << std::endl;
	return true;
}



