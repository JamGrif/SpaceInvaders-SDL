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
/// <param name="pParams"></param>
void PlayerLives::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_livesRequired = pParams->livesRequired;
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
