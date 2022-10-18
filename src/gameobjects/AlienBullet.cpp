#include "pch.h"
#include "gameobjects/AlienBullet.h"

#include "core/GameWindow.h"
#include "gameobjects/Player.h"
#include "gameobjects/Block.h"

#define ABULLET_SCREEN_BUFFER 40	// How close the alien bullet can get to the screen edge before something happens

#define PlayerPathY 592

AlienBullet::AlienBullet()
	:m_pLevelPlayer(nullptr), m_pAllBlocks(nullptr), m_screenHeight(TheGameWindow::Instance()->getWindowHeight())
{
}

AlienBullet::~AlienBullet()
{
}

/// <summary>
/// Set all values in AlienBullet class and parent classes
/// </summary>
void AlienBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams, Player* levelPlayer, std::vector<Block*>* levelBlocksPtr)
{
	assert(levelPlayer);
	assert(levelBlocksPtr);

	SDLGameObject::loadObject(pParams);

	m_pLevelPlayer = levelPlayer;
	m_pAllBlocks = levelBlocksPtr;
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
		for (auto block : *m_pAllBlocks)
		{
			if (checkCollision(this, block))
			{
				block->hit();
				m_bDestroy = true;
				return;
			}
		}
	}

	// Only check for player collision if near players line (where only player will be)
	if (m_position.getY() >= PlayerPathY)
	{
		// Check collision of bullet against player
		if (checkCollision(this, m_pLevelPlayer))
		{
			m_bDestroy = true;
			m_pLevelPlayer->setDying();
		}
	}
}
