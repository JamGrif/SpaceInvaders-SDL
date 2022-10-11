#include "pch.h"
#include "gameobjects/BaseBullet.h"


BaseBullet::BaseBullet()
	:SDLGameObject(), m_bDestroy(false)
{
}

BaseBullet::~BaseBullet()
{
}

void BaseBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);


}

void BaseBullet::drawObject()
{
	SDLGameObject::drawObject();
}

