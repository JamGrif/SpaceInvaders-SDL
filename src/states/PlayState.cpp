#include "pch.h"
#include "states/PlayState.h"

#include <ctime>
#include <cstdlib>

#include "core/Game.h"
#include "core/SpriteManager.h"
#include "core/Renderer.h"
#include "core/InputHandler.h"
#include "gameobjects/Player.h"
#include "gameobjects/Alien.h"
#include "gameobjects/BaseGameObject.h"
#include "states/PauseState.h"
#include "states/GameOverState.h"
#include "states/utility/GameStateMachine.h"
#include "level/Level.h"
#include "level/BaseLayer.h"
#include "level/ObjectLayer.h"
#include "gameobjects/utility/BulletHandler.h"

const std::string PlayState::s_playID = "PLAY";

float currentTime = 0.0f;
float maxTime = 1000.0;

void PlayState::updateState()
{
	BaseState::updateState();

	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ESC))
	{
		TheGame::Instance()->getStateMachine()->indicateAChange(StateMachineAction::Pause);
	}

	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::One))
	{
		TheGame::Instance()->getStateMachine()->indicateAChange(StateMachineAction::GameOver);
	}

	// Check
	
	currentTime += TheProgramClock::Instance()->getDeltaTime();
	if (currentTime >= maxTime)
	{
		currentTime = 0.0f;
		if (m_allAliens->size())
		{
			int randomNumber = rand() % ((m_allAliens->size() - 1) - 0 + 1);
			m_allAliens->at(randomNumber)->setDying();
		}
	}

	// Check all aliens and remove any dead ones
	for (int i = 0; i < m_allAliens->size(); i++)
	{
		if (m_allAliens->at(i)->isDead())
		{
			// remove alien from vector
			m_allAliens->erase(m_allAliens->begin() + i);
			continue;
		}
	}

	for (auto aliens : *m_allAliens)
	{
		// If any aliens have reached the edge of the screen, they will all need to move down next frame
		if (aliens->checkIfReachedEdge())
		{
			// Tell all the aliens they need to switch
			for (auto aliens : *m_allAliens)
			{
				aliens->switchDirections();
			}
			break;
		}
	}

	TheBulletHandler::Instance()->updateBullets();
	
}

void PlayState::renderState()
{
	BaseState::renderState();

	TheBulletHandler::Instance()->drawBullets();
}

bool PlayState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering PlayState-=-=-=-=-=-" << std::endl;

	loadLevel("PlayState.tmx");


	ObjectLayer* temp = dynamic_cast<ObjectLayer*>(m_pStateLevel->getLayer(LayerIndex::objectLayer));
	m_allAliens = &temp->getAlienObjects();

	srand(time(0));

	return true;
}

bool PlayState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting PlayState-=-=-=-=-=-" << std::endl;

	m_allAliens = nullptr;

	TheBulletHandler::Instance()->cleanBullets();

	delete m_pStateLevel;

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
