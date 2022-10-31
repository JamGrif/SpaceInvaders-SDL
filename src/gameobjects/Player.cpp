#include "pch.h"
#include "gameobjects/Player.h"

#include "core/Game.h"
#include "core/InputHandler.h"
#include "core/SoundManager.h"
#include "gameobjects/utility/BulletHandler.h"

// Row values from playerSheet.png
enum class PlayerSpriteRow
{
	Alive = 0,
	Dead  = 1
};

Player::Player()
	:SDLGameObject(), m_bDead(false), m_bDying(false),
	m_currentDyingTime_ms(0), m_selectedDyingTime_ms(2000), m_respawnPosition(0,0),
	m_bReadyToShoot(true), m_selectedShotWaitTime_ms(500), m_currentShotWaitTime_ms(0)
{
}

Player::~Player()
{
}

/// <summary>
/// Set all values in Player and parent classes
/// </summary>
void Player::loadObject(std::unique_ptr<LoaderParams> pParams)
{
	// Use the starting position as the respawn position
	m_respawnPosition.setX(static_cast<float>(pParams->xPos));
	m_respawnPosition.setY(static_cast<float>(pParams->yPos));

	SDLGameObject::loadObject(std::move(pParams));
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
		m_currentDyingTime_ms += TheProgramClock::Instance()->getDeltaTime_ms();
		if (m_currentDyingTime_ms >= m_selectedDyingTime_ms)
			m_bDead = true;
		
		return;
	}

	// Ensure player is not touching right wall
	if (m_position.getX() + m_objectWidth < m_screenWidth - EDGE_SCREEN_BUFFER)
	{
		if (TheInputHandler::Instance()->isKeyDown(Keyboard::D))
		{
			m_velocity.setX(m_velocity.getX() + m_movementSpeed);
		}
	}
	// Ensure player is not touching left wall
	if (m_position.getX() > EDGE_SCREEN_BUFFER)
	{
		if (TheInputHandler::Instance()->isKeyDown(Keyboard::A))
		{
			m_velocity.setX(m_velocity.getX() + -m_movementSpeed);
		}
	}

	if (m_bReadyToShoot)
	{
		// Spawn PlayerBullet on input
		if (TheInputHandler::Instance()->isKeyDown(Keyboard::SPACE))
		{
			// If shot was fired, begin shot cool down
			if (m_stateBulletHandler.lock()->addPlayerBullet(static_cast<int32_t>(m_position.getX() + (m_objectWidth / 2)), static_cast<int32_t>(m_position.getY() - m_objectHeight)))
				m_bReadyToShoot = false;
		}
	}
	else
	{
		m_currentShotWaitTime_ms += TheProgramClock::Instance()->getDeltaTime_ms();
		if (m_currentShotWaitTime_ms >= m_selectedShotWaitTime_ms)
		{
			m_currentShotWaitTime_ms = 0;
			m_bReadyToShoot = true;
		}
	}
}

/// <summary>
/// Reset all values to default
/// </summary>
void Player::respawnPlayer()
{
	//m_objectTextureID = "player";
	//m_framesInSprite = 1;
	
	m_currentSpriteRow = static_cast<uint8_t>(PlayerSpriteRow::Alive);

	m_position.setX(m_respawnPosition.getX());
	m_position.setY(m_respawnPosition.getY());

	m_bDead = false;
	m_bDying = false;

	m_currentDyingTime_ms = 0;

	TheGame::Instance()->decreaseCurrentLives();
}

/// <summary>
/// Set player status to dying and do any other actions related to that
/// </summary>
void Player::setDying()
{
	m_bDying = true;
	//m_objectTextureID = "playerDead";
	m_currentSpriteRow = static_cast<uint8_t>(PlayerSpriteRow::Dead);
	m_framesInSprite = 2;
	m_animationSpeed_ms = 150;

	TheSoundManager::Instance()->playSound("playerExplosion");
}

