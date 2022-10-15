#include "pch.h"
#include "gameobjects/SDLGameObject.h"

#include "SDL2/SDL.h"

#include "core/SpriteManager.h"
#include "core/Window.h"

SDLGameObject::SDLGameObject()
	:BaseGameObject(), m_position(0, 0), m_velocity(0, 0), m_objectWidth(0), m_objectHeight(0),
	m_currentSpriteFrame(1), m_framesInSprite(0), m_animationSpeed_ms(0), m_movementSpeed(0),
	m_screenWidth(0), m_screenHeight(0), m_bFlipImage(false)
{
}

SDLGameObject::~SDLGameObject()
{
}

/// <summary>
/// Sell all values in SDLGameObject class
/// </summary>
void SDLGameObject::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	m_position = Vector2D(static_cast<float>(pParams->xPos), static_cast<float>(pParams->yPos));

	m_objectTextureID = pParams->textureID;
	m_framesInSprite = pParams->numFrames;
	m_animationSpeed_ms = pParams->animationSpeed;
	m_movementSpeed = pParams->movementSpeed;

	m_screenWidth = TheWindow::Instance()->getWindowWidth();
	m_screenHeight = TheWindow::Instance()->getWindowHeight();

	// The Object width and height is the dimensions of the current sprite frame on its sprite sheet
	Sprite* temp = TheSpriteManager::Instance()->getSpriteViaID(m_objectTextureID);
	if (temp)
	{
		temp->setUpIndividualSpriteDimensions(pParams->numFrames);
		m_objectWidth = temp->getIndividualDimensions()->w;
		m_objectHeight = temp->getIndividualDimensions()->h;
	}
}

/// <summary>
/// Use the SpriteManager to draw the sprite
/// Chooses which sprite to draw by using the sprites ID assigned to it at creation
/// </summary>
void SDLGameObject::drawObject()
{
	SpriteManager::Instance()->drawSpriteFrame(
		m_objectTextureID,
		static_cast<int>(m_position.getX()),
		static_cast<int>(m_position.getY()),
		m_objectWidth,
		m_objectHeight,
		m_currentSpriteFrame,
		m_bFlipImage);
}

/// <summary>
/// Update the values used in this class
/// </summary>
void SDLGameObject::updateObject()
{
	m_position += m_velocity;

	// Update animation unless animationSpeed is 0
	if (m_animationSpeed_ms)
	{
		m_currentSpriteFrame = static_cast<int>(((SDL_GetTicks() / m_animationSpeed_ms) % m_framesInSprite));
	}
	else
	{
		m_currentSpriteFrame = 0;
	}
}

