#include "pch.h"
#include "gameobjects/AlienBullet.h"

#include "core/GameWindow.h"
#include "gameobjects/Player.h"
#include "gameobjects/Block.h"

// How close the alien bullet can get to the screen edge before something happens
static constexpr uint16_t ABULLET_SCREEN_BUFFER = 40;

// The Y value of the players path
static constexpr uint16_t PLAYER_PATH_Y = 592;

AlienBullet::AlienBullet()
	:m_pAllBlocks(nullptr)
{
}

AlienBullet::~AlienBullet()
{
}

/// <summary>
/// Set all values in AlienBullet class and parent classes
/// </summary>
void AlienBullet::loadObject(std::unique_ptr<LoaderParams> pParams, std::weak_ptr<Player> pLevelPlayer, std::vector<std::shared_ptr<Block>>* pLevelBlocks)
{
	assert(pLevelBlocks);

	m_classType = "AlienBullet";

	m_pLevelPlayer = pLevelPlayer;
	m_pAllBlocks = pLevelBlocks;

	SDLGameObject::loadObject(std::move(pParams));
}

/// <summary>
/// Call parent class draw function
/// </summary>
void AlienBullet::drawObject()
{
	BaseBullet::drawObject();
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
void AlienBullet::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setY(m_movementSpeed);

	// Check if bullet hit edge of play area
	if (m_position.getY() >= m_screenHeight - ABULLET_SCREEN_BUFFER)
	{
		m_bDestroy = true;
		return;
	}

	// Only check for block collision if below finish line (where the blocks are)
	if (m_position.getY() >= LEVEL_FINISH_LINE_Y)
	{
		// Check collision of bullet against blocks
		for (const auto& block : *m_pAllBlocks)
		{
			if (checkCollision(this, block.get()))
			{
				block->hitObject();
				m_bDestroy = true;
				return;
			}
		}
	}

	// Only check for player collision if near players line (where only player will be)
	if (m_position.getY() >= PLAYER_PATH_Y)
	{
		// Check collision of bullet against player
		if (checkCollision(this, m_pLevelPlayer.lock().get()))
		{
			m_bDestroy = true;
			m_pLevelPlayer.lock()->setDying();
		}
	}
}
