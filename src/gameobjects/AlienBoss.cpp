#include "pch.h"
#include "gameobjects/AlienBoss.h"

#include "core/Game.h"

AlienBoss::AlienBoss()
	:SDLGameObject(), m_minimumRespawnTime_ms(2000), m_maximumRespawnTime_ms(4000), m_selectedRespawnTime_ms(0), m_currentRespawnTime_ms(0),
	m_minimumScoreWorth(60), m_maximumScoreWorth(140), m_selectedScoreWorth(0)
{

}

AlienBoss::~AlienBoss()
{

}

void AlienBoss::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);
	m_aliveTextureID = pParams->textureID;

	reset();


	//m_scoreWorth = pParams->scoreWorth;
}

void AlienBoss::drawObject()
{
	SDLGameObject::drawObject();
}

void AlienBoss::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setX(0);

	if (m_bDying)
	{
		m_timeAloudDying += TheProgramClock::Instance()->getDeltaTime();
		if (m_timeAloudDying >= m_timeSpentDying)
		{
			setDead();
			return;
		}
	}
	
	// If alien is not active, it is waiting to respawn
	if (!m_bActive)
	{
		m_currentRespawnTime_ms += TheProgramClock::Instance()->getDeltaTime();

		if (m_currentRespawnTime_ms >= m_selectedRespawnTime_ms)
		{
			std::cout << m_currentRespawnTime_ms << std::endl;
			m_bActive = true;
			return;
		}
	}
	// Alien is active 
	else
	{
		// AlienBoss moving right
		if (m_direction == MovingDirection::Right)
		{
			m_velocity.setX(m_movementSpeed);

			//Alien has left the screen
			if (m_position.getX() >= rightSpawnPosition.getX())
			{
				m_currentRespawnTime_ms = 0;
				reset();
			}

		}
		// AlienBoss moving left
		else
		{
			m_velocity.setX(-m_movementSpeed);

			//Alien has left the screen
			if (m_position.getX() <= leftSpawnPosition.getX())
			{
				m_currentRespawnTime_ms = 0;
				reset();
			}
		}
		
	}




}

void AlienBoss::reset()
{
	std::cout << __FUNCTION__ << std::endl;
	m_currentRespawnTime_ms = 0;

	m_selectedRespawnTime_ms = getRandomNumber(m_minimumRespawnTime_ms, m_maximumRespawnTime_ms);
	m_selectedScoreWorth = getRandomNumber(m_minimumScoreWorth, m_maximumScoreWorth);

	// Decide direction
	m_direction = static_cast<MovingDirection>(getRandomNumber(static_cast<int>(MovingDirection::Left), static_cast<int>(MovingDirection::Right)));
	if (m_direction == MovingDirection::Left)
	{
		m_position = rightSpawnPosition;
	}
	else
	{
		m_position = leftSpawnPosition;
	}

	//std::cout << m_objectTextureID << std::endl;
	//std::cout << m_aliveTextureID << std::endl;
	m_objectTextureID = m_aliveTextureID;
	//m_framesInSprite = 1;


	m_bActive = false;

	//m_bDead = false;

	//std::cout << "selectedrespawntime" << m_selectedRespawnTime_ms << std::endl;
	//std::cout << "selectedscoreworth" << m_selectedScoreWorth << std::endl;
	//std::cout << "currentrespawntime" << m_currentRespawnTime_ms << std::endl;
}


void AlienBoss::setDying()
{
	//m_framesInSprite = 2;
	m_objectTextureID = m_deadTextureID;
	m_bDying = true;
}

void AlienBoss::setDead()
{
	m_bDying = false;
	if (m_bActive)
	{
		TheGame::Instance()->increaseCurrentScore(m_selectedScoreWorth);
		m_bActive = false;
		reset();
	}
}
