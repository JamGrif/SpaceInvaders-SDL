#include "pch.h"
#include "states/PlayState.h"


#include "core/Game.h"
#include "core/InputHandler.h"
#include "states/utility/GameStateMachine.h"
#include "gameobjects/Player.h"
#include "gameobjects/Alien.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/BaseGameObject.h"
#include "gameobjects/utility/BulletHandler.h"
#include "level/Level.h"
#include "level/ObjectLayer.h"

const std::string PlayState::s_playID = "PLAY";


std::string PlayState::s_textCallback1()
{
	return std::to_string(TheGame::Instance()->getCurrentScore());
}

// Required Y value of alien for them to win
#define alienWinLineHeight 500

static bool g_bResetLives = true;
static bool g_bResetScore = true;


void PlayState::updateState()
{
	BaseState::updateState();

	//std::cout << m_alienBoss->getPosition().getX() << std::endl;

	// If esc is pressed then push PauseState into the FSM
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ESC))
	{
		TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::pushPause);
	}

	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ONE))
	{
		m_alienBoss->setDead();
	}

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
	if (m_bAllowedToSpawnBullets)
	{
		m_currentNextShotTime_ms += static_cast<int>(TheProgramClock::Instance()->getDeltaTime());
		if (m_SelectedNextShotTime_ms == 0)
		{
			// Set time until next alien shoots (between minNextShotTime and maxNextShotTime)
			m_SelectedNextShotTime_ms = getRandomNumber(m_minNextShotTime_ms, m_maxNextShotTime_ms);
			//m_SelectedNextShotTime_ms = rand() % (m_maxNextShotTime_ms - m_minNextShotTime_ms + 1) + m_minNextShotTime_ms;
			//std::cout << m_SelectedNextShotTime_ms << std::endl;
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
				aliens->switchDirections();
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
		//TheGame::Instance()->setGameOutcome(GameStateOutcome::Win_KilledAllAliens);
		//TheGame::Instance()->getStateMachine()->setStateUpdate(StateMachineAction::changeToGameOver);
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

	// Update all bullets
	TheBulletHandler::Instance()->updateBullets();
	
}

void PlayState::renderState()
{
	BaseState::renderState();

	TheBulletHandler::Instance()->drawBullets();
}

PlayState::PlayState()
	:m_currentNextShotTime_ms(0), m_maxNextShotTime_ms(2000), m_minNextShotTime_ms(500), m_SelectedNextShotTime_ms(0)
{

}


PlayState::~PlayState()
{

}

bool PlayState::onEnterState()
{
	std::cout << "-=-=-=-=-=-Entering PlayState-=-=-=-=-=-" << std::endl;

	loadLevel("PlayState.tmx");


	ObjectLayer* temp = dynamic_cast<ObjectLayer*>(m_pStateLevel->getLayer(LayerIndex::objectLayer));
	m_allAliens = &temp->getAlienObjects();
	m_player = temp->getPlayerObject();
	m_alienBoss = temp->getAlienBossObject();

	//bFirstCheckDying = false;
	//allowedToSpawnBullets = true;

	m_textCallbackFunctions.push_back(0);
	m_textCallbackFunctions.push_back(s_textCallback1);

	setCallbacks();

	BulletHandler::Instance()->setLevel(m_pStateLevel);

	if (g_bResetLives)
		TheGame::Instance()->resetCurrentLives();

	if (g_bResetScore)
		TheGame::Instance()->resetCurrentScore();

	

	return true;
}

bool PlayState::onExitState()
{
	std::cout << "-=-=-=-=-=-Exiting PlayState-=-=-=-=-=-" << std::endl;

	BaseState::onExitState();

	m_allAliens = nullptr;
	m_player = nullptr;

	TheBulletHandler::Instance()->clearBullets();

	//delete m_pStateLevel;

	return true;
}

