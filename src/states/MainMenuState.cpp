#include "pch.h"
#include "states/MainMenuState.h"

#include "states/GameStateMachine.h"
#include "core/TextureManager.h"

#include "core/Game.h"
#include "core/Renderer.h"
#include "gameobjects/MenuButton.h"
#include "states/PlayState.h"

#include "states/StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";



void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}


void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}

void MainMenuState::update()
{
	// i think because when you click the first button it unloads the stuff but then it tries to update the second button
	for (auto o : m_gameObjects)
	{
		o->update();
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MainMenuState::onEnter()
{
	// Parse the state
	StateParser stateParser;
	stateParser.parseState("res/test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	// Push any callbacks into the m_callbacks array, inherited from MenuState
	m_callbacks.push_back(0); // pushback = callbackID starts from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	// Set the callbacks for menu items
	setCallbacks(m_callbacks);


	std::cout << "Entering MenuState" << std::endl;
	return true;
}

bool MainMenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	// Clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "Exiting MenuState" << std::endl;
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// Go through the game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		// If they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<MenuButton*>(m_gameObjects[i])) // use dynamic_cast to check if the object is a MenuButton type
		{
			// Use the objects callbackID as the index into the callbacks vector and assign the correct function
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}
