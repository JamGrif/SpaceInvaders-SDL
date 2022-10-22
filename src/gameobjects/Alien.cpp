#include "pch.h"
#include "gameobjects/Alien.h"

#include "core/Game.h"
#include "core/SoundManager.h"

Alien::Alien()
	:SDLGameObject(), m_downAmount(15), m_bDying(false),
	m_timeSpentDying_ms(0), m_timeAloudDying_ms(200), m_selectedScoreWorth(0),
	m_direction(MovingDirection::None)
{
}

Alien::~Alien()
{
}

/// <summary>
/// Set all values in Alien class and parent classes
/// </summary>
void Alien::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_deadTextureID = "alienDead";
	m_selectedScoreWorth = pParams->scoreWorth;
	m_direction = MovingDirection::Left;
}

/// <summary>
/// Call parent class draw function
/// </summary>
void Alien::drawObject()
{
	SDLGameObject::drawObject();
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
void Alien::updateObject()
{
	SDLGameObject::updateObject();

	// If dying, continue dying timer
	if (m_bDying)
	{
		m_timeSpentDying_ms += TheProgramClock::Instance()->getDeltaTime_ms();
		if (m_timeSpentDying_ms >= m_timeAloudDying_ms)
			m_bDestroy = true;
	
		return;
	}

	// Move alien
	if (m_direction == MovingDirection::Left)
	{
		m_position.setX(m_position.getX() - m_movementSpeed);
	}
	else if (m_direction == MovingDirection::Right)
	{
		m_position.setX(m_position.getX() + m_movementSpeed);
	}
}

/// <summary>
/// Set alien status to dying and do any other actions related to that
/// </summary>
void Alien::setDying()
{
	m_bDying = true;

	m_objectTextureID = m_deadTextureID;
	TheGame::Instance()->increaseCurrentScore(m_selectedScoreWorth);

	TheSoundManager::Instance()->playSound("alienExplosion");
}

/// <summary>
/// Check if alien has reached either edge of screen and return true if so
/// </summary>
bool Alien::checkIfReachedEdge() const
{
	// If alien hit edge
	if (m_position.getX() < EDGE_SCREEN_BUFFER || m_position.getX() + m_objectWidth > m_screenWidth - EDGE_SCREEN_BUFFER)
	{
		return true;
	}

	return false;
}

/// <summary>
/// Toggle the direction the alien moves
/// </summary>
void Alien::switchDirection()
{
	// Swap direction
	m_direction = m_direction == MovingDirection::Left ? MovingDirection::Right : MovingDirection::Left;

	// Move alien down
	m_position.setY(m_position.getY() + m_downAmount);
}
