#include "pch.h"
#include "gameobjects/PlayerLives.h"

#include "gameobjects/Player.h"

#include "core/Game.h"

PlayerLives::PlayerLives()
	:SDLGameObject(), m_livesRequired(0), m_bDraw(true)
{
}

PlayerLives::~PlayerLives()
{
	//m_pPlayer = nullptr;
}

void PlayerLives::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);
	m_livesRequired = pParams->livesRequired;

}

void PlayerLives::drawObject()
{
	if (m_livesRequired > TheGame::Instance()->getCurrentLives())
		return;

	SDLGameObject::drawObject();
}

void PlayerLives::updateObject()
{
	SDLGameObject::updateObject();

}
