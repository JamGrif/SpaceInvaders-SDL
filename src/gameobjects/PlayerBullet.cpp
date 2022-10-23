#include "pch.h"
#include "gameobjects/PlayerBullet.h"

#include "gameobjects/Alien.h"
#include "gameobjects/AlienBoss.h"
#include "gameobjects/Block.h"

// How close the player bullet can get to the screen edge before something happens
static constexpr uint16_t PBULLET_SCREEN_BUFFER = 115;

// The Y value the AlienBoss will travel along
static constexpr uint16_t ALIEN_BOSS_PATH_Y = 140;


PlayerBullet::PlayerBullet()
	:BaseBullet(), m_pAllAliens(nullptr), m_pAllBlocks(nullptr)
{
}

PlayerBullet::~PlayerBullet()
{
	//std::cout << "ded" << std::endl;
}

/// <summary>
/// Set all values in PlayerBullet class and parent classes
/// </summary>
void PlayerBullet::loadObject(std::unique_ptr<LoaderParams> pParams, std::vector<std::shared_ptr<Alien>>* pLevelAliens, std::weak_ptr<AlienBoss> pAlienBoss, std::vector<std::shared_ptr<Block>>* pLevelBlocks)
{
	assert(pLevelAliens);
	assert(pLevelBlocks);

	BaseBullet::loadObject(std::move(pParams));

	m_classType = "PlayerBullet";

	m_pAllAliens = pLevelAliens;
	m_pAlienBoss = pAlienBoss;
	m_pAllBlocks = pLevelBlocks;
}

/// <summary>
/// Call parent class draw function
/// </summary>
void PlayerBullet::drawObject()
{
	BaseBullet::drawObject();
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
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

	// Only check for alien collision if above finish line (where only aliens will be)
	if (m_position.getY() <= LEVEL_FINISH_LINE_Y)
	{
		// Check collision of bullet against aliens
		for (const auto& alien : *m_pAllAliens)
		{
			if (checkCollision(this, alien.get()))
			{
				alien->setDying();
				m_bDestroy = true;
				return;
			}
		}
	}

	// Only check for collision of alien boss if above specified line (where the alien boss will always be)
	if (m_position.getY() <= ALIEN_BOSS_PATH_Y)
	{
		// If bullet collided with alienboss
		if (checkCollision(this, m_pAlienBoss.lock().get()))
		{
			m_pAlienBoss.lock()->setDying();
			m_bDestroy = true;
			return;
		}
	}
}
