#include "MenuState.h"

#include "Game.h"
#include "SDLRenderer.h"
#include "MenuButton.h"
#include "PlayState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked" << std::endl;
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}


void MenuState::s_exitFromMenu()
{
	std::cout << "Exit button clicked" << std::endl;
	TheGame::Instance()->quit();
}

void MenuState::update()
{
	// i think because when you click the first button it unloads the stuff but then it tries to update the second button
	for (auto o : m_gameObjects)
	{
		o->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	if (!TheTextureManager::Instance()->load("res/sprites/button.png", "playbutton", TheRenderer::Instance()->getRendererPtr()))
		return false;

	if (!TheTextureManager::Instance()->load("res/sprites/exit.png", "exitbutton", TheRenderer::Instance()->getRendererPtr()))
		return false;

	GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering MenuState" << std::endl;
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

	std::cout << "Exiting MenuState" << std::endl;
	return true;
}
