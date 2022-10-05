#include "pch.h"
#include "gameobjects/Bullet.h"

PlayerBullet::PlayerBullet()
	:SDLGameObject()
{
	std::cout << "Bullet made" << std::endl;
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	//m_objectWidth = 20;
	//m_objectWi

	std::cout << "bulletwidth is " << m_objectWidth << std::endl;
	std::cout << "bulletheight is " << m_objectHeight << std::endl;

	m_movementSpeed = 3;
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
}
