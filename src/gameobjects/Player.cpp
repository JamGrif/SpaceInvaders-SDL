#include "pch.h"
#include "gameobjects/Player.h"

#include "core/InputHandler.h"
#include "core/Game.h"
#include "gameobjects/utility/BulletHandler.h"
#include "core/SoundManager.h"

Player::Player()
	:SDLGameObject(), m_bDead(false), m_bDying(false), m_respawnPosition(0,0)
{
}

Player::~Player()
{
}

/// <summary>
/// Responsible for setting all variables used in Player and inherited class
/// </summary>
void Player::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	// Use the starting position as the respawn position
	m_respawnPosition.setX(static_cast<float>(pParams->xPos));
	m_respawnPosition.setY(static_cast<float>(pParams->yPos));
}

void Player::drawObject()
{
	SDLGameObject::drawObject();
}

void Player::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setX(0);
	m_velocity.setY(0);

	if (m_bDead)
	{
		std::cout << "dead" << std::endl;
		return;
	}

	if (m_bDying)
	{
		m_timeSpentDying += static_cast<float>(TheProgramClock::Instance()->getDeltaTime());
		if (m_timeSpentDying >= m_timeMaxDying)
			m_bDead = true;
		
		return;
	}

	// Move Right
	if (m_position.getX() + m_objectWidth < m_screenWidth - edgeScreenBuffer)
	{
		if (TheInputHandler::Instance()->isKeyDown(Keyboard::D))
		{
			m_velocity.setX(m_movementSpeed);
		}
	}

	// Move Left
	if (m_position.getX() > edgeScreenBuffer)
	{
		if (TheInputHandler::Instance()->isKeyDown(Keyboard::A))
		{
			m_velocity.setX(-m_movementSpeed);
		}
	}

	// Spawn PlayerBullet
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::SPACE))
	{
		TheBulletHandler::Instance()->addPlayerBullet(static_cast<int>(m_position.getX()+(m_objectWidth/2)), static_cast<int>(m_position.getY() - m_objectHeight));
	}

}

/// <summary>
/// Reset all values to default
/// </summary>
void Player::respawn()
{
	m_objectTextureID = "player";
	m_framesInSprite = 1;

	m_position.setX(m_respawnPosition.getX());
	m_position.setY(m_respawnPosition.getY());

	m_bDead = false;
	m_bDying = false;

	m_timeSpentDying = 0.0f;

	TheGame::Instance()->decreaseCurrentLives();
}

void Player::setDying()
{
	m_bDying = true;
	m_objectTextureID = "playerDead";
	m_framesInSprite = 2;
	m_animationSpeed = 150;

	TheSoundManager::Instance()->playSound("playerExplosion");
}

