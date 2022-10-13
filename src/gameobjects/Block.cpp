#include "pch.h"
#include "gameobjects/Block.h"

Block::Block()
	:SDLGameObject(), m_bDestoryed(false), m_blockHealth(0)
{
}

Block::~Block()
{
}

/// <summary>
/// Call parent class load function
/// </summary>
void Block::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);
}

/// <summary>
/// Call parent class draw function
/// </summary>
void Block::drawObject()
{
	SDLGameObject::drawObject();
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
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

/// <summary>
/// Decrement the blocks health
/// Called when the block is hit by a bullet
/// </summary>
void Block::hit()
{
	m_blockHealth++;
}
