#include "pch.h"
#include "gameobjects/utility/BulletHandler.h"
#include "gameobjects/Bullet.h"

#include "level/Level.h"
#include "level/ObjectLayer.h"

BulletHandler* BulletHandler::s_pInstance = nullptr;


void BulletHandler::addPlayerBullet(int xPos, int yPos)
{
	// Only one PlayerBullet can exist at one time
	if (m_playerBullet)
		return;

	// Create bullet
	m_playerBullet = new PlayerBullet();

	// Setup initial bullet values
	std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();

	tempLoaderParams->x = xPos;
	tempLoaderParams->y = yPos;
	tempLoaderParams->textureID = "playerBullet";
	ObjectLayer* temp = dynamic_cast<ObjectLayer*>(m_level->getLayer(LayerIndex::objectLayer)); // Give the bullet the vector of the level aliens

	// Set initial bullet values
	m_playerBullet->loadObject(tempLoaderParams, &temp->getAlienObjects());
}

void BulletHandler::addAlienBullet(int xPos, int yPos)
{
	// Only a certain amount of alienBullets can exist
	if (m_alienBullets.size() >= m_maxAlienBullets)
		return;

	AlienBullet* alienBullet = new AlienBullet();

	// Setup initial bullet values
	std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();

	tempLoaderParams->x = xPos;
	tempLoaderParams->y = yPos;
	tempLoaderParams->textureID = "alienBullet";

	alienBullet->loadObject(tempLoaderParams);
	m_alienBullets.push_back(alienBullet);
}

void BulletHandler::updateBullets()
{
	if (m_playerBullet)
	{
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

	//for (auto alien : m_alienBullets)
	//{
	//	alien->updateObject();
	//}

	for (int i = 0; i < m_alienBullets.size(); i++)
	{
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

void BulletHandler::drawBullets()
{
	if (m_playerBullet)
		m_playerBullet->drawObject();

	for (auto bullet : m_alienBullets)
	{
		bullet->drawObject();
	}

}

void BulletHandler::cleanBullets()
{
	if (m_playerBullet)
	{
		delete m_playerBullet;
		m_playerBullet = nullptr;
	}
}

BulletHandler* BulletHandler::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new BulletHandler();
	}
	return s_pInstance;
}

BulletHandler::BulletHandler()
	:m_playerBullet(nullptr), m_level(nullptr)

{
}
