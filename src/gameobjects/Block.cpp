#include "pch.h"
#include "gameobjects/Block.h"

#include "core/SoundManager.h"

// Numbers correspond to sprite frames in "block.png"
enum class BlockHealth
{
	NoDamage		= 3,
	SlightDamage	= 2,
	MinorDamage		= 1,
	MajorDamage		= 0,
	Gone			= -1
};

Block::Block()
	:SDLGameObject(), m_blockHealth(BlockHealth::NoDamage)
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

	m_currentSpriteFrame = static_cast<uint8_t>(m_blockHealth);
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

	if (m_blockHealth == BlockHealth::Gone)
		m_bDestroy = true;
	else
		m_currentSpriteFrame = static_cast<uint8_t>(m_blockHealth);
}

/// <summary>
/// Decrement the blocks health
/// Called when the block is hit by a bullet
/// </summary>
void Block::hitObject()
{
	m_blockHealth = static_cast<BlockHealth>(static_cast<int32_t>(m_blockHealth) - 1);
	TheSoundManager::Instance()->playSound("blockBreak");
}
