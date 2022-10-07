#include "pch.h"
#include "gameobjects/Bullet.h"

#include "core/Window.h"

#include "gameobjects/Alien.h"
#include "gameobjects/Player.h"

#include "misc/Collision.h"

#define playerBulletScreenEdge 115
#define alienBulletScreenEdge 40

PlayerBullet::PlayerBullet()
	:SDLGameObject(), m_bDestroy(false), m_pAllAliens(nullptr)
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams, std::vector<Alien*>* levelAliensPtr)
{
	SDLGameObject::loadObject(pParams);

	m_pAllAliens = levelAliensPtr;
}

void PlayerBullet::drawObject()
{
	SDLGameObject::drawObject();
}

void PlayerBullet::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setY(-m_movementSpeed);

	// If bullet reached edge of screen
	if (m_position.getY() + m_objectHeight <= playerBulletScreenEdge)
	{
		m_bDestroy = true;
	}

	// If bullet collided with an alien
	for (auto alien : *m_pAllAliens)
	{
		if (checkCollision(this, alien))
		{
			alien->setDying();
			m_bDestroy = true;
			break;
		}
	}
}

// ----------------

AlienBullet::AlienBullet()
	:m_bDestroy(false), m_pLevelPlayer(nullptr), m_screenHeight(TheWindow::Instance()->getWindowHeight())
{
}

AlienBullet::~AlienBullet()
{
}

void AlienBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams, Player* levelPlayer)
{
	SDLGameObject::loadObject(pParams);

	m_pLevelPlayer = levelPlayer;
}

void AlienBullet::drawObject()
{
	SDLGameObject::drawObject();
}

void AlienBullet::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setY(m_movementSpeed);

	// Bullet gets destroyed if it collides with an alien or reaches edge of screen
	if (m_position.getY() >= m_screenHeight - alienBulletScreenEdge)
	{
		m_bDestroy = true;
	}

	// If bullet collided with an alien
	if (checkCollision(this, m_pLevelPlayer))
	{
		m_bDestroy = true;
		m_pLevelPlayer->setDying();
	}
}
