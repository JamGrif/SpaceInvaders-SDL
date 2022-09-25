#include "pch.h"
#include "Enemy.h"

#include "SDL.h"

Enemy::Enemy(const LoaderParams* pParams)
	:SDLGameObject(pParams)
{

}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_position.setX(m_position.getX() + 1);
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Enemy::clean()
{
}
