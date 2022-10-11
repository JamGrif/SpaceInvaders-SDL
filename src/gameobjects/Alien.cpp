#include "pch.h"
#include "gameobjects/Alien.h"

#include "core/Game.h"
#include "core/SoundManager.h"

Alien::Alien()
	:SDLGameObject(), m_downAmount(15), m_bDying(false), m_bDead(false), m_timeSpentDying_ms(0), m_timeAloudDying_ms(200), m_selectedScoreWorth(0),
	m_direction(MovingDirection::None)
{
}

Alien::~Alien()
{
}

/// <summary>
/// Responsible for setting all variables used in Enemy and inherited class
/// </summary>
void Alien::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_deadTextureID = "alienDead";
	m_selectedScoreWorth = pParams->scoreWorth;
	m_direction = MovingDirection::Left;
}


void Alien::drawObject()
{
	SDLGameObject::drawObject();
}

void Alien::updateObject()
{
	if (m_bDead)
		return;
	
	if (m_bDying)
	{
		m_timeSpentDying_ms += TheProgramClock::Instance()->getDeltaTime();
		if (m_timeSpentDying_ms >= m_timeAloudDying_ms)
			m_bDead = true;
	
		return;
	}

	SDLGameObject::updateObject();

	if (m_direction == MovingDirection::Left)
	{
		m_position.setX(m_position.getX() - m_movementSpeed);
	}
	else if (m_direction == MovingDirection::Right)
	{
		m_position.setX(m_position.getX() + m_movementSpeed);
	}

}

// Checks if alien has reached the edge of screen and needs to move down with all other aliens
bool Alien::checkIfReachedEdge()
{
	if (m_position.getX() < edgeScreenBuffer || m_position.getX() + m_objectWidth > m_screenWidth - edgeScreenBuffer)
	{
		return true;
	}

	return false;
}

void Alien::switchDirection()
{
	// Swap direction
	m_direction = m_direction == MovingDirection::Left ? MovingDirection::Right : MovingDirection::Left;

	// Move aliens down
	m_position.setY(m_position.getY() + m_downAmount);
}

void Alien::setDying()
{
	m_bDying = true;
	TheSoundManager::Instance()->playSound("alienExplosion");
	TheGame::Instance()->increaseCurrentScore(m_selectedScoreWorth);
	m_objectTextureID = m_deadTextureID;
}

