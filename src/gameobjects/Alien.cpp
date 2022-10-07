#include "pch.h"
#include "gameobjects/Alien.h"

#include "SDL2/SDL.h"

#include "core/SoundManager.h"

Alien::Alien()
	:SDLGameObject(), m_bMoveLeft(true), m_downAmount(15), m_bDying(false), m_bDead(false), m_timeSpentDying(0), m_timeAloudDying(200)
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
}


void Alien::drawObject()
{
	if (m_bDead)
		return;

	if (m_bDying)
	{
		m_objectTextureID = m_deadTextureID;
		
	}
	
	SDLGameObject::drawObject();
}

void Alien::updateObject()
{
	if (m_bDead)
		return;
	
	if (m_bDying)
	{
		m_timeSpentDying += static_cast<float>(TheProgramClock::Instance()->getDeltaTime());
		if (m_timeSpentDying >= m_timeAloudDying)
			m_bDead = true;
	
		return;
	}

	SDLGameObject::updateObject();

	if (m_bMoveLeft)
	{
		m_position.setX(m_position.getX() - m_movementSpeed);
	}
	else
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

void Alien::switchDirections()
{
	m_bMoveLeft = !m_bMoveLeft;
	m_position.setY(m_position.getY() + m_downAmount);
}

void Alien::setDying()
{
	m_bDying = true;
	TheSoundManager::Instance()->playSound("alienExplosion");
}

