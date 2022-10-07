#include "pch.h"
#include "gameobjects/PlayerLives.h"

#include "gameobjects/Player.h"

PlayerLives::PlayerLives()
	:SDLGameObject(), m_livesRequired(0), m_bDraw(true), m_pPlayer(nullptr)
{
}

PlayerLives::~PlayerLives()
{
	m_pPlayer = nullptr;
}

void PlayerLives::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);
	m_livesRequired = pParams->livesRequired;

}

void PlayerLives::drawObject()
{
	if (m_livesRequired > m_pPlayer->getPlayerLives())
		return;

	SDLGameObject::drawObject();
}

void PlayerLives::updateObject()
{
	SDLGameObject::updateObject();

}
