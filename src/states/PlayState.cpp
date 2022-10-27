#include "pch.h"
#include "states/PlayState.h"

#include "core/Game.h"
#include "core/InputHandler.h"
#include "core/SoundManager.h"
#include "gameobjects/Alien.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/Block.h"
#include "gameobjects/Player.h"
#include "gameobjects/utility/BulletHandler.h"
#include "level/Level.h"
#include "states/utility/GameStateMachine.h"

// Required Y value of alien for them to win
static constexpr uint16_t ALIEN_WIN_LINE_HEIGHT = 500;


static bool g_bResetLives = true;	// Should lives be reset at PlayState begin?
static bool g_bResetScore = true;	// Should score be reset at PlatState begin?

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
	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ESC))
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::pushPause);

#if _DEBUG
	// Quick way to get to GameOverState while debugging
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ONE))
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
#endif

	if (m_bInPrep)
	{
		m_currentPrepTime_ms += TheProgramClock::Instance()->getDeltaTime_ms();
		if (m_currentPrepTime_ms >= m_selectedPrepTime_ms)
		{
			m_bInPrep = false;
		}
		return;
	}

	/*
		Update all gameobjects
	*/

	BaseState::updateState();

	// Update each alien object and destroy it if needed
	auto it_alien = m_allAliens.begin();
	while (it_alien != m_allAliens.end())
	{
		if ((*it_alien)->getDestroy())
		{
			it_alien = m_allAliens.erase(it_alien);
			continue;
		}
		else
		{
			(*it_alien)->updateObject();

			// If any aliens have reached the edge of the screen, they will all need to move down next frame
			if ((*it_alien)->checkIfReachedEdge())
			{
				// Tell all the aliens they need to switch
				for (const auto& aliens : m_allAliens)
				{
					aliens->switchDirection();
				}
				break;
			}

			it_alien++;
		}
	}

	// Update each block object and destroy it if needed
	auto it_block = m_allBlocks.begin();
	while (it_block != m_allBlocks.end())
	{
		if ((*it_block)->getDestroy())
		{
			it_block = m_allBlocks.erase(it_block);
			continue;
		}
		else
		{
			(*it_block)->updateObject();
			it_block++;
		}
	}

	// Update all bullets
	m_pBulletHandler->updateBullets();

	/*
		Check player's status
	*/
	
	// If player is dead, determine whether to respawn them or change state to game over
	if (m_pPlayer.lock()->getDead())
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
			m_pPlayer.lock()->respawnPlayer();
		}
	}

	// When player is dying, take action (clearing bullets) once until they next start dying
	
	if (!m_bFirstCheckDying)
	{
		if (m_pPlayer.lock()->getDying())
		{
			m_bFirstCheckDying = true;
			m_bAllowedToSpawnBullets = false;
			m_pBulletHandler->clearBullets();
		}
	}

	/*
		Check for alien bullet spawning
	*/

	// Spawn a bullet at a random alien
	if (m_bAllowedToSpawnBullets)
	{
		m_currentNextShotTime_ms += static_cast<int>(TheProgramClock::Instance()->getDeltaTime_ms());
		if (m_selectedNextShotTime_ms == 0)
		{
			// Set time until next alien shoots (between minNextShotTime and maxNextShotTime)
			m_selectedNextShotTime_ms = getRandomNumber(m_minNextShotTime_ms, m_maxNextShotTime_ms);
		}

		if (m_currentNextShotTime_ms >= m_selectedNextShotTime_ms)
		{
			// Reset timings
			m_currentNextShotTime_ms = 0;
			m_selectedNextShotTime_ms = 0;

			if (!m_allAliens.empty())
			{
				// Pick a random alien
				int randomIndex = getRandomNumber(0, static_cast<int>(m_allAliens.size()) - 1);
				std::shared_ptr<Alien> temp = m_allAliens.at(randomIndex);

				// Spawn a bullet at selected alien
				m_pBulletHandler->addAlienBullet(static_cast<int>((temp->getPosition().getX() + (temp->getWidth() / 2))), static_cast<int>(temp->getPosition().getY()));
			}
		}
	}

	/*
		Check alien win status
	*/

	// Check if any alien has reached finish line
	for (auto alien : m_allAliens)
	{
		if (alien->getPosition().getY() >= ALIEN_WIN_LINE_HEIGHT)
		{
			g_bResetLives = true;
			g_bResetScore = true;
			TheGame::Instance()->setGameOutcome(GameStateOutcome::Lose_AliensReachedEnd);
			TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
		}
	}

	// If all aliens are dead
	if (m_allAliens.empty())
	{
		g_bResetLives = false;
		g_bResetScore = false;

		TheGame::Instance()->increaseCurrentLives();
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToPlay);
	}



	
}

/// <summary>
/// Call parent class render function and draw any spawned in bullets
/// </summary>
void PlayState::renderState()
{
	BaseState::renderState();

	for (const auto& a : m_allAliens)
	{
		if (!a->getDestroy())
			a->drawObject();
	}

	for (const auto& b : m_allBlocks)
	{
		if (!b->getDestroy())
			b->drawObject();
	}

	m_pBulletHandler->drawBullets();
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

	// Assign IDs to functions, push 0 first so IDs start at 1
	m_textCallbackFunctions.push_back(0);
	m_textCallbackFunctions.push_back(s_textCallback1);

	setCallbacks();

	// If required, reset current lives and score
	if (g_bResetLives)
		TheGame::Instance()->resetCurrentLives();

	if (g_bResetScore)
		TheGame::Instance()->resetCurrentScore();

	// Do one pass of updating gameobjects to set initial states before entering prep stage
	//BaseState::updateState();

	// Go through all gameobjects and move any alien objects and block objects to their respective vectors
	auto it = m_allGameObjects.begin();
	while (it != m_allGameObjects.end())
	{
		// Check if gameobject is a Block object and move it to its own vector
		auto block = std::dynamic_pointer_cast<Block>(*it);
		if (block)
		{
			m_allBlocks.push_back(block);
			it = m_allGameObjects.erase(it);
			continue;
		}

		// Check if gameobject is an Alien object and not AlienBoss object and move it to its own vector
		auto alien = std::dynamic_pointer_cast<Alien>(*it);
		if (alien && !std::dynamic_pointer_cast<AlienBoss>(*it))
		{
			m_allAliens.push_back(std::dynamic_pointer_cast<Alien>(*it));
			it = m_allGameObjects.erase(it);
			continue;
		}

		// If gameobject is a Player, then store its address
		auto player = std::dynamic_pointer_cast<Player>(*it);
		if (player)
		{
			m_pPlayer = player;
			it++;
			continue;
		}

		// If gameobject is an AlienBoss, then store its address
		auto alienboss = std::dynamic_pointer_cast<AlienBoss>(*it);
		if (alienboss)
		{
			m_pAlienBoss = alienboss;
			it++;
			continue;
		}

		it++;
	}

	m_allGameObjects.shrink_to_fit();

	// Create bullet handler and let player class store a pointer to it
	m_pBulletHandler = std::make_shared<BulletHandler>(m_allBlocks, m_allAliens, m_pPlayer, m_pAlienBoss);
	m_pPlayer.lock()->setBulletHandler(m_pBulletHandler);

	return true;
}

/// <summary>
/// Call parent class onExitState function and clear any active bullets
/// </summary>
bool PlayState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting PlayState-=-=-=-=-=-" << std::endl;
	BaseState::onExitState();

	TheSoundManager::Instance()->stopAllSounds();

	return true;
}

