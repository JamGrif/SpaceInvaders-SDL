#include "pch.h"
#include "gameobjects/AlienBullet.h"

#include "core/Window.h"
#include "gameobjects/Player.h"
#include "gameobjects/Block.h"

#define ABULLET_SCREEN_BUFFER 40	// How close the alien bullet can get to the screen edge before something happens

#define PlayerPathY 592


AlienBullet::AlienBullet()
	:m_pLevelPlayer(nullptr), m_screenHeight(TheWindow::Instance()->getWindowHeight())
{
}

AlienBullet::~AlienBullet()
{
}

void AlienBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams, Player* levelPlayer, std::vector<Block*>* levelBlocksPtr)
{
	SDLGameObject::loadObject(pParams);

	m_pLevelPlayer = levelPlayer;
	m_pAllBlocks = levelBlocksPtr;
}

void AlienBullet::drawObject()
{
	BaseBullet::drawObject();
}

void AlienBullet::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setY(m_movementSpeed);

	// Bullet gets destroyed if it collides with an alien or reaches edge of screen
	if (m_position.getY() >= m_screenHeight - ABULLET_SCREEN_BUFFER)
	{
		m_bDestroy = true;
	}

	// Only check for block collision if below finish line (where the blocks are)
	if (m_position.getY() >= LevelFinishLineY)
	{
		//std::cout << "checking collision of blocks" << std::endl;
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
		//std::cout << "checking collision against player" << std::endl;
		// Check collision of bullet against player
		if (checkCollision(this, m_pLevelPlayer))
		{
			m_bDestroy = true;
			m_pLevelPlayer->setDying();
		}
	}
	
}
