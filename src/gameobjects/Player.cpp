#include "pch.h"
#include "gameobjects/Player.h"

#include "core/Game.h"
#include "core/InputHandler.h"
#include "core/SoundManager.h"
#include "gameobjects/utility/BulletHandler.h"

Player::Player()
	:SDLGameObject(), m_bDead(false), m_bDying(false),
	m_timeSpentDying_ms(0), m_timeAloudDying_ms(2000), m_respawnPosition(0,0)
{
}

Player::~Player()
{
}

/// <summary>
/// Set all values in Player and parent classes
/// </summary>
void Player::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	// Use the starting position as the respawn position
	m_respawnPosition.setX(static_cast<float>(pParams->xPos));
	m_respawnPosition.setY(static_cast<float>(pParams->yPos));
}

/// <summary>
/// Call parent class draw function
/// </summary>
void Player::drawObject()
{
	SDLGameObject::drawObject();
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
void Player::updateObject()
{
	SDLGameObject::updateObject();

	// Reset velocity
	m_velocity.setX(0);
	m_velocity.setY(0);

	if (m_bDead)
		return;

	// If dying, continue dying timer
	if (m_bDying)
	{
		m_timeSpentDying_ms += TheProgramClock::Instance()->getDeltaTime_ms();
		if (m_timeSpentDying_ms >= m_timeAloudDying_ms)
			m_bDead = true;
		
		return;
	}

	// Move player in direction from input
	if (m_position.getX() + m_objectWidth < m_screenWidth - EDGE_SCREEN_BUFFER)
	{
		if (TheInputHandler::Instance()->isKeyDown(Keyboard::D))
		{
			m_velocity.setX(m_movementSpeed);
		}
	}

	if (m_position.getX() > EDGE_SCREEN_BUFFER)
	{
		if (TheInputHandler::Instance()->isKeyDown(Keyboard::A))
		{
			m_velocity.setX(-m_movementSpeed);
		}
	}

	// Spawn PlayerBullet on input
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::SPACE))
	{
		//TheBulletHandler::Instance()->addPlayerBullet(static_cast<int>(m_position.getX()+(m_objectWidth/2)), static_cast<int>(m_position.getY() - m_objectHeight));
		m_stateBulletHandler.lock()->addPlayerBullet(static_cast<int>(m_position.getX() + (m_objectWidth / 2)), static_cast<int>(m_position.getY() - m_objectHeight));
	}

}

/// <summary>
/// Reset all values to default
/// </summary>
void Player::respawnPlayer()
{
	m_objectTextureID = "player";
	m_framesInSprite = 1;

	m_position.setX(m_respawnPosition.getX());
	m_position.setY(m_respawnPosition.getY());

	m_bDead = false;
	m_bDying = false;

	m_timeSpentDying_ms = 0;

	TheGame::Instance()->decreaseCurrentLives();
}

/// <summary>
/// Set player status to dying and do any other actions related to that
/// </summary>
void Player::setDying()
{
	m_bDying = true;
	m_objectTextureID = "playerDead";
	m_framesInSprite = 2;
	m_animationSpeed_ms = 150;

	TheSoundManager::Instance()->playSound("playerExplosion");
}

