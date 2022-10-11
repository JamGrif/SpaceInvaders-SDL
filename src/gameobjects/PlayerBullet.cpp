#include "pch.h"
#include "gameobjects/PlayerBullet.h"

#include "gameobjects/Alien.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/Block.h"

#define PBULLET_SCREEN_BUFFER 115	// How close the player bullet can get to the screen edge before something happens

#define AlienBossPathY 140


PlayerBullet::PlayerBullet()
	:BaseBullet(), m_pAllAliens(nullptr), m_pAlienBoss(nullptr)
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::loadObject(std::unique_ptr<LoaderParams> const& pParams, std::vector<Alien*>* levelAliensPtr, AlienBoss* alienBossPtr, std::vector<Block*>* levelBlocksPtr)
{
	BaseBullet::loadObject(pParams);

	m_pAllAliens = levelAliensPtr;
	m_pAlienBoss = alienBossPtr;
	m_pAllBlocks = levelBlocksPtr;
}

void PlayerBullet::drawObject()
{
	BaseBullet::drawObject();
}

void PlayerBullet::updateObject()
{
	SDLGameObject::updateObject();

	m_velocity.setY(-m_movementSpeed);

	// If bullet reached edge of screen
	if (m_position.getY() + m_objectHeight <= PBULLET_SCREEN_BUFFER)
	{
		m_bDestroy = true;
		return;
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
	

	// Only check for alien collision if above finish line (where only aliens will be)
	if (m_position.getY() <= LevelFinishLineY)
	{
		//std::cout << "checking collision of aliens" << std::endl;
		// Check collision of bullet against aliens
		for (auto alien : *m_pAllAliens)
		{
			if (checkCollision(this, alien))
			{
				alien->setDying();
				m_bDestroy = true;
				return;
			}
		}
	}

	// Only check for collision of alien boss if above specified line (where the alien boss will always be)
	if (m_position.getY() <= AlienBossPathY)
	{
		//std::cout << "checking collision of alienboss" << std::endl;
		// If bullet collided with alienboss
		if (checkCollision(this, m_pAlienBoss))
		{
			m_pAlienBoss->setDying();
			m_bDestroy = true;
			return;
		}
	}

	
}
