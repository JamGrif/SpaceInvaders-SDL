#include "pch.h"
#include "gameobjects/Block.h"

#include "core/SoundManager.h"

Block::Block()
	:SDLGameObject(), m_blockHealth(0)
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

	m_currentSpriteFrame = m_blockHealth;
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
		//m_bDestoryed = true;
		m_bDestroy = true;
		return;
	}
	else
	{
		m_currentSpriteFrame = m_blockHealth;
	}

	
}

/// <summary>
/// Decrement the blocks health
/// Called when the block is hit by a bullet
/// </summary>
void Block::hit()
{
	TheSoundManager::Instance()->playSound("blockBreak");
	m_blockHealth++;
}
