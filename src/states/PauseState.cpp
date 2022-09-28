#include "pch.h"
#include "states/PauseState.h"

#include "core/Game.h"
#include "states/GameStateMachine.h"
#include "states/MenuState.h"
#include "core/TextureManager.h"
#include "states/MainMenuState.h"
#include "states/StateParser.h"
#include "gameobjects/MenuButton.h"

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
	StateParser stateParser;
	stateParser.parseState("res/test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	std::cout << "Entering PauseState" << std::endl;
	return true;
}

bool PauseState::onExit()
{
	for (auto o : m_gameObjects)
	{
		o->clean();
	}
	m_gameObjects.clear();

	// Clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	// Reset the mouse button states to false
	//TheInputHandler::Instance()->reset();

	std::cout << "Exiting PauseState" << std::endl;
	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// Go through the game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		// If they are of type MenuButton, then assign a callback based on the ID passed in from the file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}


