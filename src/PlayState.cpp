#include "pch.h"
#include "PlayState.h"

#include "TextureManager.h"
#include "Renderer.h"
#include "Player.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	//for (int i = 0; i < m_gameObjects.size(); i++)
	//{
	//	m_gameObjects[i]->update();
	//}

	for (auto o : m_gameObjects)
	{
		o->update();
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("res/sprites/helicopter.png", "helicopter"))
		return false;

	GameObject* player = new Player(new LoaderParams(100, 100, 128, 55, "helicopter"));
	m_gameObjects.push_back(player);

	std::cout << "Entering PlayState" << std::endl;
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("helicopter");

	std::cout << "Exiting PlayState" << std::endl;
	return true;
}
