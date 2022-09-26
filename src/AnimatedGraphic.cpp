#include "pch.h"
#include "AnimatedGraphic.h"

#include "SDL.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed)
	:SDLGameObject(pParams), m_animSpeed(animSpeed)
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
