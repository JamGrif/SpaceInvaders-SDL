#include "pch.h"
#include "gameobjects/utility/BulletHandler.h"
#include "gameobjects/Bullet.h"

BulletHandler* BulletHandler::s_pInstance = nullptr;


void BulletHandler::addPlayerBullet(int xPos, int yPos)
{
	// Only one PlayerBullet can exist at one time
	if (m_playerBullet)
		return;

	PlayerBullet* pPlayerBullet = new PlayerBullet();
	std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();

	tempLoaderParams->x = xPos;
	tempLoaderParams->y = yPos;

	tempLoaderParams->textureID = "playerBullet";

	pPlayerBullet->loadObject(tempLoaderParams);
	m_playerBullet = pPlayerBullet;
}

void BulletHandler::updateBullets()
{
	if (m_playerBullet)
		m_playerBullet->updateObject();
}

void BulletHandler::drawBullets()
{
	if (m_playerBullet)
		m_playerBullet->drawObject();
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
{
}
