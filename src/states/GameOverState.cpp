#include "pch.h"
#include "states/GameOverState.h"

#include "core/Game.h"
#include "states/GameStateMachine.h"
#include "states/MenuState.h"
#include "states/PlayState.h"
#include "core/TextureManager.h"
#include "gameobjects/AnimatedGraphic.h"
#include "states/MainMenuState.h"
#include "states/StateParser.h"
#include "gameobjects/MenuButton.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
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
	// Parse the state
	StateParser stateParser;
	stateParser.parseState("res/test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	// Set the callbacks for menu items
	setCallbacks(m_callbacks);

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

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "Exiting GameOverState" << std::endl;
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}


