#include "pch.h"
#include "gameobjects/utility/BulletHandler.h"

#include "core/SoundManager.h"
#include "gameobjects/PlayerBullet.h"
#include "gameobjects/AlienBullet.h"
#include "level/Level.h"
#include "level/ObjectLayer.h"

#define PBULLET_SPEED 6

BulletHandler* BulletHandler::s_pInstance = nullptr;

/// <summary>
/// Spawn a PlayerBullet object at specified position
/// </summary>
void BulletHandler::addPlayerBullet(int xPos, int yPos)
{
	// Only one PlayerBullet can exist at one time
	if (m_playerBullet)
		return;

	// Create bullet
	m_playerBullet = new PlayerBullet();

	// Setup initial bullet values
	std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();
	tempLoaderParams->xPos = xPos;
	tempLoaderParams->yPos = yPos;
	tempLoaderParams->textureID = "playerBullet";
	tempLoaderParams->movementSpeed = PBULLET_SPEED;

	// Get the object layer in order to retrieve other level objects
	ObjectLayer* temp = dynamic_cast<ObjectLayer*>(m_level->getLayer(LayerIndex::objectLayer)); 

	// Set initial bullet values and give it information on aliens, alienboss and level blocks
	m_playerBullet->loadObject(tempLoaderParams, &temp->getAlienObjects(), temp->getAlienBossObject(), &temp->getBlockObjects());

	TheSoundManager::Instance()->playSound("playerShoot");
}

/// <summary>
/// Spawn an AlienBullet object at specified position
/// </summary>
void BulletHandler::addAlienBullet(int xPos, int yPos)
{
	// Only a certain amount of alienBullets can exist
	if (m_alienBullets.size() >= m_maxAlienBullets)
		return;

	// Create bullet
	AlienBullet* alienBullet = new AlienBullet();

	// Setup initial bullet values
	std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();
	tempLoaderParams->xPos = xPos;
	tempLoaderParams->yPos = yPos;
	tempLoaderParams->textureID = "alienBullet";
	tempLoaderParams->numFrames = 2;
	tempLoaderParams->animationSpeed = 250;
	tempLoaderParams->movementSpeed = 6;

	// Get the object layer in order to retrieve other level objects
	ObjectLayer* temp = dynamic_cast<ObjectLayer*>(m_level->getLayer(LayerIndex::objectLayer));

	// Set initial bullet values and give it information on player and level blocks
	alienBullet->loadObject(tempLoaderParams, temp->getPlayerObject(), &temp->getBlockObjects());

	m_alienBullets.push_back(alienBullet);
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
			delete m_playerBullet;
			m_playerBullet = nullptr;
		}
		else
		{
			m_playerBullet->updateObject();
		}
	}

	for (int i = 0; i < m_alienBullets.size(); i++)
	{
		// Check deletion status of each AlienBullet
		if (m_alienBullets.at(i)->getDestroy())
		{
			m_alienBullets.erase(m_alienBullets.begin() + i);
			continue;
		}
		else
		{
			m_alienBullets.at(i)->updateObject();
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

	for (auto bullet : m_alienBullets)
	{
		bullet->drawObject();
	}
}

/// <summary>
/// Delete all created PlayerBullet and AlienBullet objects
/// </summary>
void BulletHandler::clearBullets()
{
	if (m_playerBullet)
	{
		delete m_playerBullet;
		m_playerBullet = nullptr;
	}

	for (auto bullet : m_alienBullets)
	{
		delete bullet;
	}
	m_alienBullets.clear();
}
