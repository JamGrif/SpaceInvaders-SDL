#include "pch.h"
#include "states/PlayState.h"

#include "core/Game.h"
#include "core/TextureManager.h"
#include "core/Renderer.h"
#include "core/InputHandler.h"
#include "gameobjects/Player.h"
#include "gameobjects/Enemy.h"
#include "gameobjects/GameObject.h"
#include "states/PauseState.h"
#include "states/GameOverState.h"
#include "states/utility/GameStateMachine.h"
#include "states/utility/StateParser.h"

#include "level/Level.h"
#include "level/LevelParser.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ESC))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (auto o : m_gameObjects)
	{
		o->update();
	}
	
	//// dynamic_cast to cast the GameObject* class to an SDLGameObject* class
	//if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
	//{
	//	TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
	//}

	pLevel->update();
}

void PlayState::render()
{
	for (auto o : m_gameObjects)
	{
		o->draw();
	}

	pLevel->render();
}

bool PlayState::onEnter()
{
	std::cout << "Entering PlayState" << std::endl;
	// Parse the state
	//StateParser stateParser;
	//stateParser.parseState("res/test.xml", s_playID, &m_gameObjects, &m_textureIDList);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("map1.tmx");

	return true;
}

bool PlayState::onExit()
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

	std::cout << "Exiting PlayState" << std::endl;
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

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
