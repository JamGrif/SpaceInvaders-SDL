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

#define alienWinLineHeight 500

static float currentTime = 0.0f;
static float maxTime = 1000.0;

static bool bFirstCheckDying = false;
static bool allowedToSpawnBullets = true;

void PlayState::updateState()
{
	BaseState::updateState();

	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ESC))
	{
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::pushPause);
	}

	// If player is dead, determine whether to respawn them or change state to gameover
	if (m_player->getDead())
	{
		// Player has run out of lives
		if (m_player->getPlayerLives() <= 0)
		{
			TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
		}
		else
		{
			bFirstCheckDying = false;
			allowedToSpawnBullets = true;
			m_player->respawn();
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

	// Spawn a bullet at a random alien
	if (allowedToSpawnBullets)
	{
		currentTime += static_cast<float>(TheProgramClock::Instance()->getDeltaTime());
		if (currentTime >= maxTime)
		{
			currentTime = 0.0f;
			if (m_allAliens->size())
			{
				int randomNumber = rand() % ((m_allAliens->size() - 1) - 0 + 1);

				Alien* temp = m_allAliens->at(randomNumber);
				TheBulletHandler::Instance()->addAlienBullet(static_cast<int>((temp->getPosition().getX() + (temp->getWidth() / 2))), static_cast<int>(temp->getPosition().getY()));
			}
		}
	}

	// Check if any alien has reached finish line
	for (auto alien : *m_allAliens)
	{
		if (alien->getPosition().getY() >= alienWinLineHeight)
		{
			TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
		}
	}
	

	// Check direction of aliens
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

	// If all aliens are dead
	if (m_allAliens->empty())
	{
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
	}

	if (!bFirstCheckDying)
	{
		if (m_player->getDying())
		{
			bFirstCheckDying = true;
			allowedToSpawnBullets = false;
			TheBulletHandler::Instance()->clearBullets();
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
	m_player = temp->getPlayerObject();
	allowedToSpawnBullets = true;

	BulletHandler::Instance()->setLevel(m_pStateLevel);

	srand(static_cast<unsigned int>(time(0)));

	return true;
}

bool PlayState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting PlayState-=-=-=-=-=-" << std::endl;

	m_allAliens = nullptr;
	m_player = nullptr;

	TheBulletHandler::Instance()->clearBullets();

	delete m_pStateLevel;

	return true;
}

