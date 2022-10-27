#include "pch.h"
#include "gameobjects/PlayerLives.h"

#include "core/Game.h"

PlayerLives::PlayerLives()
	:SDLGameObject(), m_livesRequired(0), m_bDraw(true)
{
}

PlayerLives::~PlayerLives()
{
}

/// <summary>
/// Set all values in PlayerLives class and parent classes
/// </summary>
void PlayerLives::loadObject(std::unique_ptr<LoaderParams> pParams)
{
	m_livesRequired = pParams->livesRequired;

	SDLGameObject::loadObject(std::move(pParams));
}

/// <summary>
/// Call parent class draw function
/// </summary>
void PlayerLives::drawObject()
{
	if (m_livesRequired > TheGame::Instance()->getCurrentLives())
		return;

	SDLGameObject::drawObject();
}

/// <summary>
/// Call parent class update function
/// </summary>
void PlayerLives::updateObject()
{
	SDLGameObject::updateObject();
}
