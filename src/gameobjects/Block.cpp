#include "pch.h"
#include "gameobjects/Block.h"

Block::Block()
	:SDLGameObject()
{

}

Block::~Block()
{

}

void Block::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);
}

void Block::drawObject()
{
	SDLGameObject::drawObject();
}

void Block::updateObject()
{
	SDLGameObject::updateObject();

	if (m_blockHealth == static_cast<int>(BlockHealth::Gone))
	{
		m_bDestoryed = true;
		return;
	}

	m_currentSpriteFrame = m_blockHealth;

}

void Block::hit()
{
	m_blockHealth++;
}
