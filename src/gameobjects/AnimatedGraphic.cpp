#include "pch.h"
#include "gameobjects/AnimatedGraphic.h"

#include "SDL.h"

AnimatedGraphic::AnimatedGraphic(int animSpeed)
	:SDLGameObject(), m_animSpeed(animSpeed)
{

}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
	constexpr int numFrames = 2;
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % numFrames));
}

void AnimatedGraphic::clean()
{

}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_animSpeed = pParams->getAnimSpeed();
}
