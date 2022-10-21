#include "pch.h"
#include "gameobjects/BaseBullet.h"

BaseBullet::BaseBullet()
	:SDLGameObject()
{
}

BaseBullet::~BaseBullet()
{
}

/// <summary>
/// Call parent class load function
/// </summary>
void BaseBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);
}

/// <summary>
/// Call parent class draw function
/// </summary>
void BaseBullet::drawObject()
{
	SDLGameObject::drawObject();
}
