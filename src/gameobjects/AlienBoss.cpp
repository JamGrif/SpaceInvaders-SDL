#include "pch.h"
#include "gameobjects/AlienBoss.h"

AlienBoss::AlienBoss()
	:Alien(), m_minimumRespawnTime_ms(2000), m_maximumRespawnTime_ms(4000),
	m_selectedRespawnTime_ms(0), m_currentRespawnTime_ms(0), m_minimumScoreWorth(60), m_maximumScoreWorth(140),
	leftSpawnPosition{-100, 100}, rightSpawnPosition{820, 100}
{
}

AlienBoss::~AlienBoss()
{
}

void AlienBoss::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);
	m_aliveTextureID = pParams->textureID;

	m_deadTextureID = "alienBossDead";

	resetAlien();
}

void AlienBoss::drawObject()
{
	Alien::drawObject();
}

void AlienBoss::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setX(0);

	// If alien is dying, it is waiting to die
	if (m_bDying)
	{
		m_timeSpentDying_ms += TheProgramClock::Instance()->getDeltaTime();
		if (m_timeSpentDying_ms >= m_timeAloudDying_ms)
			resetAlien();
		
		return;
	}
	
	// If alien is dead, it is waiting to respawn
	if (m_bDead)
	{
		m_currentRespawnTime_ms += TheProgramClock::Instance()->getDeltaTime();
		if (m_currentRespawnTime_ms >= m_selectedRespawnTime_ms)
			m_bDead = false;
		
		return;
	}

	// Here if alien is not dying / dead
	
	// AlienBoss moving right
	if (m_direction == MovingDirection::Right)
	{
		m_velocity.setX(m_movementSpeed);

		//Alien has left the screen
		if (m_position.getX() >= rightSpawnPosition.getX())
			resetAlien();
		

	}
	// AlienBoss moving left
	else if (m_direction == MovingDirection::Left)
	{
		m_velocity.setX(-m_movementSpeed);

		//Alien has left the screen
		if (m_position.getX() <= leftSpawnPosition.getX())
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
	m_position = m_direction == MovingDirection::Left ? rightSpawnPosition : leftSpawnPosition;

	// Reset timing variables
	m_currentRespawnTime_ms = 0;
	m_timeSpentDying_ms = 0;

	// Set texture back to alive
	m_objectTextureID = m_aliveTextureID;

	// Set alien to dead - allowing it to start its respawn timer
	m_bDead = true;
	m_bDying = false;
}
