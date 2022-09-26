#include "pch.h"
#include "PlayState.h"

#include "TextureManager.h"
#include "Renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "GameOverState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	//for (int i = 0; i < m_gameObjects.size(); i++)
	//{
	//	m_gameObjects[i]->update();
	//}

	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ESC))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (auto o : m_gameObjects)
	{
		o->update();
	}

	// dynamic_cast to cast the GameObject* class to an SDLGameObject* class
	if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
	{
		TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
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

	if (!TheTextureManager::Instance()->load("res/sprites/helicopter2.png", "helicopter2"))
		return false;

	GameObject* player = new Player(new LoaderParams(400, 100, 128, 55, "helicopter"));
	m_gameObjects.push_back(player);

	GameObject* enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2"));
	m_gameObjects.push_back(enemy);

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

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of p1
	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	// Calculate the sides of p2
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	// If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}
