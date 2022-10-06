#include "pch.h"
#include "gameobjects/Bullet.h"

#include "core/Window.h"

#include "gameobjects/Alien.h"

#include "misc/Collision.h"

#define playerBulletScreenEdge 115
#define alienBulletScreenEdge 30

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

	m_movementSpeed = 6;

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

	// Bullet gets destroyed if it collides with an alien or reaches edge of screen
	if (m_position.getY() + m_objectHeight <= playerBulletScreenEdge)
	{
		m_bDestroy = true;
	}

	for (auto alien : *m_pAllAliens)
	{
		if (checkCollision(this, alien))
		{
			alien->setDying();
			m_bDestroy = true;
		}
	}
}

bool PlayerBullet::getDestroy()
{
	return m_bDestroy;
}

// ----------------

AlienBullet::AlienBullet()
	:m_bDestroy(false), m_pPlayer(nullptr), m_screenHeight(TheWindow::Instance()->getWindowHeight())
{
}

AlienBullet::~AlienBullet()
{
}

void AlienBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	pParams->numFrames = 2;
	SDLGameObject::loadObject(pParams);

	m_movementSpeed = 5;
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
}

bool AlienBullet::getDestroy()
{
	return m_bDestroy;
}
