#include "pch.h"
#include "gameobjects/AlienBoss.h"

#include "core/SoundManager.h"

AlienBoss::AlienBoss()
	:Alien(), m_bDead(false), m_minimumRespawnTime_ms(5000), m_maximumRespawnTime_ms(1000), m_selectedRespawnTime_ms(0),
	m_currentRespawnTime_ms(0), m_minimumScoreWorth(60), m_maximumScoreWorth(140),
	m_leftSpawnPosition{-100, 100}, m_rightSpawnPosition{820, 100}, m_bSoundPlaying(false)
{
}

AlienBoss::~AlienBoss()
{
	TheSoundManager::Instance()->stopSound(ALIEN_BOSS_CHANNEL);
}

/// <summary>
/// Set all values in AlienBoss class and parent classes
/// </summary>
/// <param name="pParams"></param>
void AlienBoss::loadObject(std::unique_ptr<LoaderParams> pParams)
{
	m_aliveTextureID = pParams->textureID;

	m_deadTextureID = "alienBossDead";

	SDLGameObject::loadObject(std::move(pParams));

	resetAlien();
}

/// <summary>
/// Call parent class draw function
/// </summary>
void AlienBoss::drawObject()
{
	Alien::drawObject();
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
void AlienBoss::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setX(0);

	// If dying, continue dying timer
	if (m_bDying)
	{
		if (m_bSoundPlaying)
		{
			m_bSoundPlaying = false;
			TheSoundManager::Instance()->stopSound(ALIEN_BOSS_CHANNEL);
		}

		m_timeSpentDying_ms += TheProgramClock::Instance()->getDeltaTime_ms();
		if (m_timeSpentDying_ms >= m_timeAloudDying_ms)
			resetAlien();
		
		return;
	}
	
	// If dead, continue respawn timer
	if (m_bDead)
	{
		m_currentRespawnTime_ms += TheProgramClock::Instance()->getDeltaTime_ms();
		if (m_currentRespawnTime_ms >= m_selectedRespawnTime_ms)
			m_bDead = false;
		
		return;
	}

	if (!m_bSoundPlaying)
	{
		TheSoundManager::Instance()->playSound("alienBossMove", true);
		m_bSoundPlaying = true;
	}
	
	// Move alien in specified direction
	if (m_direction == MovingDirection::Right)
	{
		m_velocity.setX(m_movementSpeed);

		//Alien has left the screen
		if (m_position.getX() >= m_rightSpawnPosition.getX())
			resetAlien();
	}
	else if (m_direction == MovingDirection::Left)
	{
		m_velocity.setX(-m_movementSpeed);

		//Alien has left the screen
		if (m_position.getX() <= m_leftSpawnPosition.getX())
			resetAlien();
	}
}

/// <summary>
/// Reset and update the AlienBoss' values for when it next respawns
/// </summary>
void AlienBoss::resetAlien()
{
	// Select a new random RespawnTime and ScoreWorth
	m_selectedRespawnTime_ms = getRandomNumber(m_minimumRespawnTime_ms, m_maximumRespawnTime_ms);
	m_selectedScoreWorth = getRandomNumber(m_minimumScoreWorth, m_maximumScoreWorth);

	// Randomly decide starting direction and set its position
	m_direction = static_cast<MovingDirection>(getRandomNumber(static_cast<int>(MovingDirection::Left), static_cast<int>(MovingDirection::Right)));
	m_position = m_direction == MovingDirection::Left ? m_rightSpawnPosition : m_leftSpawnPosition;

	// Reset timing variables
	m_currentRespawnTime_ms = 0;
	m_timeSpentDying_ms = 0;

	// Set texture back to alive
	m_objectTextureID = m_aliveTextureID;

	// Set alien to dead - allowing it to start its respawn timer
	m_bDead = true;
	m_bDying = false;

	// Sound
	m_bSoundPlaying = false;
	TheSoundManager::Instance()->stopSound(ALIEN_BOSS_CHANNEL);
}
