#include "pch.h"
#include "gameobjects/utility/BulletHandler.h"

#include "core/SoundManager.h"
#include "gameobjects/PlayerBullet.h"
#include "gameobjects/AlienBullet.h"
#include "level/Level.h"

// Player bullet speed
#define PBULLET_SPEED 3

// Alien bullets will have a random speed between this range
#define ABULLET_MIN_SPEED 2
#define ABULLET_MAX_SPEED 4

// Alien bullets animation speed
#define ABULLET_ANIMATION_SPEED 250

BulletHandler::BulletHandler(std::vector<std::shared_ptr<Block>>& allblocks, std::vector<std::shared_ptr<Alien>>& allAliens, std::weak_ptr<Player> pPlayer, std::weak_ptr<AlienBoss> pAlienboss)
	: m_allBlocks(&allblocks), m_allAliens(&allAliens), m_player(pPlayer), m_alienBoss(pAlienboss), m_playerBullet(nullptr), m_maxAlienBullets(5)
{
	m_alienBullets.reserve(static_cast<size_t>(m_maxAlienBullets));
}

BulletHandler::~BulletHandler()
{
}

/// <summary>
/// Spawn a PlayerBullet object at specified position
/// </summary>
bool BulletHandler::addPlayerBullet(int32_t xPos, int32_t yPos)
{
	// Only one PlayerBullet can exist at one time
	if (m_playerBullet)
		return false;

	// Create bullet
	m_playerBullet = std::make_unique<PlayerBullet>();

	// Setup initial bullet values
	std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();
	tempLoaderParams->xPos = xPos;
	tempLoaderParams->yPos = yPos;
	tempLoaderParams->textureID = "playerBullet";
	tempLoaderParams->movementSpeed = PBULLET_SPEED;

	// Set initial bullet values and give it information on aliens, alienboss and level blocks
	m_playerBullet->loadObject(std::move(tempLoaderParams), m_allAliens, m_alienBoss, m_allBlocks);

	TheSoundManager::Instance()->playSound("playerShoot");

	return true;
}

/// <summary>
/// Spawn an AlienBullet object at specified position
/// </summary>
void BulletHandler::addAlienBullet(int32_t xPos, int32_t yPos)
{
	// Only a certain amount of alienBullets can exist
	if (m_alienBullets.size() >= m_maxAlienBullets)
		return;

	// Create bullet
	std::unique_ptr<AlienBullet> alienBullet = std::make_unique<AlienBullet>();

	// Setup initial bullet values
	std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();
	tempLoaderParams->xPos = xPos;
	tempLoaderParams->yPos = yPos;
	tempLoaderParams->textureID = "alienBullet";
	tempLoaderParams->numFrames = 2;
	tempLoaderParams->animationSpeed = ABULLET_ANIMATION_SPEED;
	tempLoaderParams->movementSpeed = static_cast<float>(getRandomNumber(ABULLET_MIN_SPEED, ABULLET_MAX_SPEED));

	// Set initial bullet values and give it information on player and level blocks
	alienBullet->loadObject(std::move(tempLoaderParams), m_player, m_allBlocks);

	// Add newly created bullet into total alien bullet vector
	m_alienBullets.push_back(std::move(alienBullet));

	TheSoundManager::Instance()->playSound("alienShoot");
}

/// <summary>
/// Update both PlayerBullet and AlienBullet objects
/// </summary>
void BulletHandler::updateBullets()
{
	if (m_playerBullet)
	{
		// Check deletion status of the PlayerBullet
		if (m_playerBullet->getDestroy())
		{
			m_playerBullet.reset();
		}
		else
		{
			m_playerBullet->updateObject();
		}
	}

	auto it = m_alienBullets.begin();
	while (it != m_alienBullets.end())
	{
		// Check deletion status of each AlienBullet
		if ((*it)->getDestroy())
		{
			it = m_alienBullets.erase(it);
		}
		else
		{
			(*it)->updateObject();
			it++;
		}
	}
}

/// <summary>
/// Draw both PlayerBullet and AlienBullet objects
/// </summary>
void BulletHandler::drawBullets()
{
	if (m_playerBullet)
		m_playerBullet->drawObject();

	for (const auto& bullet : m_alienBullets)
	{
		bullet->drawObject();
	}
}

/// <summary>
/// Delete all created PlayerBullet and AlienBullet objects
/// </summary>
void BulletHandler::clearBullets()
{
	m_playerBullet = nullptr;

	m_alienBullets.clear();
}
