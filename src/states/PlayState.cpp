#include "pch.h"
#include "states/PlayState.h"

#include "core/Game.h"
#include "core/InputHandler.h"
#include "core/SoundManager.h"
#include "gameobjects/Alien.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/BaseGameObject.h"
#include "gameobjects/Block.h"
#include "gameobjects/Player.h"
#include "gameobjects/utility/BulletHandler.h"
#include "level/Level.h"
#include "level/ObjectLayer.h"
#include "states/utility/GameStateMachine.h"

// Required Y value of alien for them to win
#define alienWinLineHeight 500

static bool g_bResetLives = true;
static bool g_bResetScore = true;

const std::string PlayState::s_playID = "PLAY";

/// <summary>
/// Set in editor: textCallbackID 1
/// </summary>
std::string PlayState::s_textCallback1()
{
	return std::to_string(TheGame::Instance()->getCurrentScore());
}

/// <summary>
/// Calls parent class update function and updates the game objects used in the game
/// </summary>
void PlayState::updateState()
{
	//if (m_bInPrep)
	//{
	//	m_currentPrepTime += TheProgramClock::Instance()->getDeltaTime_ms();
	//	if (m_currentPrepTime >= m_selectedPretTime)
	//	{
	//		m_bInPrep = false;
	//	}
	//	return;
	//}

	BaseState::updateState();

	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ESC))
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::pushPause);
	
	//if (TheInputHandler::Instance()->isKeyDown(Keyboard::ONE))
	//	TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
	
	// If player is dead, determine whether to respawn them or change state to game over
	if (m_player->getDead())
	{
		// Player has run out of lives
		if (TheGame::Instance()->getCurrentLives() <= 0)
		{
			g_bResetLives = true;
			g_bResetScore = true;
			TheGame::Instance()->setGameOutcome(GameStateOutcome::Lose_NoLives);
			TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
		}
		else
		{
			m_bFirstCheckDying = false;
			m_bAllowedToSpawnBullets = true;
			m_player->respawnPlayer();
		}
	}

	// Check all aliens and remove any dead ones
	for (int i = 0; i < m_allAliens->size(); i++)
	{
		if (m_allAliens->at(i)->getDead())
		{
			// remove alien from vector
			m_allAliens->erase(m_allAliens->begin() + i);
			continue;
		}
	}

	// Spawn a bullet at a random alien
	if (m_bAllowedToSpawnBullets)
	{
		m_currentNextShotTime_ms += static_cast<int>(TheProgramClock::Instance()->getDeltaTime_ms());
		if (m_SelectedNextShotTime_ms == 0)
		{
			// Set time until next alien shoots (between minNextShotTime and maxNextShotTime)
			m_SelectedNextShotTime_ms = getRandomNumber(m_minNextShotTime_ms, m_maxNextShotTime_ms);
		}

		if (m_currentNextShotTime_ms >= m_SelectedNextShotTime_ms)
		{
			// Reset timings
			m_currentNextShotTime_ms = 0;
			m_SelectedNextShotTime_ms = 0;

			if (!m_allAliens->empty())
			{
				// Pick a random alien
				int randomIndex = rand() % ((m_allAliens->size() - 1) - 0 + 1);
				Alien* temp = m_allAliens->at(randomIndex);

				// Spawn a bullet at selected alien
				TheBulletHandler::Instance()->addAlienBullet(static_cast<int>((temp->getPosition().getX() + (temp->getWidth() / 2))), static_cast<int>(temp->getPosition().getY()));
			}
		}
	}

	// Check if any alien has reached finish line
	for (auto alien : *m_allAliens)
	{
		if (alien->getPosition().getY() >= alienWinLineHeight)
		{
			g_bResetLives = true;
			g_bResetScore = true;
			TheGame::Instance()->setGameOutcome(GameStateOutcome::Lose_AliensReachedEnd);
			TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
		}
	}
	

	// Check and update direction of aliens
	for (auto aliens : *m_allAliens)
	{
		// If any aliens have reached the edge of the screen, they will all need to move down next frame
		if (aliens->checkIfReachedEdge())
		{
			// Tell all the aliens they need to switch
			for (auto aliens : *m_allAliens)
			{
				aliens->switchDirection();
			}
			break;
		}
	}

	// If all aliens are dead
	if (m_allAliens->empty())
	{
		g_bResetLives = false;
		g_bResetScore = false;

		TheGame::Instance()->increaseCurrentLives();
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToPlay);
	}

	// When player is dying, take action (clearing bullets) once until they next start dying
	if (!m_bFirstCheckDying)
	{
		if (m_player->getDying())
		{
			m_bFirstCheckDying = true;
			m_bAllowedToSpawnBullets = false;
			TheBulletHandler::Instance()->clearBullets();
		}
	}

	// Check all blocks and remove any destroyed
	for (int i = 0; i < m_allBlocks->size(); i++)
	{
		if (m_allBlocks->at(i)->isDestroyed())
		{
			// remove block from vector
			m_allBlocks->erase(m_allBlocks->begin() + i);
			continue;
		}
	}

	// Update all bullets
	TheBulletHandler::Instance()->updateBullets();
}

/// <summary>
/// Call parent class render function and draw any spawned in bullets
/// </summary>
void PlayState::renderState()
{
	BaseState::renderState();

	TheBulletHandler::Instance()->drawBullets();
}

/// <summary>
/// Loads the level and sets the callback functions used in PlayState
/// Also sets up pointers to specific game objects, used during gameplay
/// </summary>
bool PlayState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering PlayState-=-=-=-=-=-" << std::endl;

	loadLevel("PlayState.tmx");

	TheSoundManager::Instance()->playSound("roundReset");

	ObjectLayer* temp = dynamic_cast<ObjectLayer*>(m_pStateLevel->getLayer(LayerIndex::objectLayer));
	m_allAliens = &temp->getAlienObjects();
	m_player = temp->getPlayerObject();
	m_alienBoss = temp->getAlienBossObject();
	m_allBlocks = &temp->getBlockObjects();

	// Assign IDs to functions, push 0 first so IDs start at 1
	m_textCallbackFunctions.push_back(0);
	m_textCallbackFunctions.push_back(s_textCallback1);

	setCallbacks();

	BulletHandler::Instance()->setLevel(m_pStateLevel);

	// If required, reset current lives and score
	if (g_bResetLives)
		TheGame::Instance()->resetCurrentLives();

	if (g_bResetScore)
		TheGame::Instance()->resetCurrentScore();

	// Do one pass of updating gameobjects to set initial states before entering prep stage
	//BaseState::updateState();

	return true;
}

/// <summary>
/// Call parent class onExitState function and clear any active bullets
/// </summary>
/// <returns></returns>
bool PlayState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting PlayState-=-=-=-=-=-" << std::endl;

	BaseState::onExitState();

	m_player = nullptr;
	m_alienBoss = nullptr;
	m_allAliens = nullptr;
	m_allBlocks = nullptr;

	TheBulletHandler::Instance()->clearBullets();

	return true;
}

