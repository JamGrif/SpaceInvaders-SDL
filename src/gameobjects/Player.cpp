#include "pch.h"
#include "gameobjects/Player.h"

#include "core/InputHandler.h"
#include "core/SpriteManager.h"

#include "gameobjects/utility/BulletHandler.h"

Player::Player()
	:SDLGameObject()
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

