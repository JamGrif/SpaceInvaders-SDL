#include "pch.h"
#include "gameobjects/Enemy.h"

#include "SDL.h"

Enemy::Enemy()
	:SDLGameObject()
{

}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	if (m_position.getY() < 0)
	{
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 400)
	{
		m_velocity.setY(-2);
	}

	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	SDLGameObject::update();
}

void Enemy::clean()
{
}

void Enemy::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_velocity.setY(2);
	//m_velocity.setX(0.001);
}
