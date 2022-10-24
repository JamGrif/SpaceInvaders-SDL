#include "pch.h"
#include "gameobjects/SDLGameObject.h"

#include "SDL2/SDL.h"

#include "core/SpriteManager.h"
#include "core/GameWindow.h"

SDLGameObject::SDLGameObject()
	:BaseGameObject(), m_position(0, 0), m_velocity(0, 0), m_objectWidth(0), m_objectHeight(0),
	m_objectAttributes{ 0,0,0,0 },m_currentSpriteFrame(1), m_framesInSprite(0), m_animationSpeed_ms(0),
	m_movementSpeed(0), m_screenWidth(0), m_screenHeight(0), m_bFlipImage(false), m_spriteRotation(0.0)
{
}

SDLGameObject::~SDLGameObject()
{
}

/// <summary>
/// Sell all values in SDLGameObject class
/// </summary>
void SDLGameObject::loadObject(std::unique_ptr<LoaderParams> pParams)
{
	m_position = Vector2D(static_cast<float>(pParams->xPos), static_cast<float>(pParams->yPos));
	m_classType = pParams->classType;

	m_objectTextureID = pParams->textureID;
	m_framesInSprite = pParams->numFrames;
	m_animationSpeed_ms = pParams->animationSpeed;
	m_movementSpeed = pParams->movementSpeed;

	m_screenWidth = TheGameWindow::Instance()->getWindowWidth();
	m_screenHeight = TheGameWindow::Instance()->getWindowHeight();

	// The Object width and height is the dimensions of the current sprite frame on its sprite sheet
	std::weak_ptr<Sprite> temp = TheSpriteManager::Instance()->getSpriteViaID(m_objectTextureID);
	if (!temp.expired())
	{
		temp.lock()->setUpIndividualSpriteDimensions(pParams->numFrames);
		m_objectWidth = temp.lock()->getIndividualDimensions()->w;
		m_objectHeight = temp.lock()->getIndividualDimensions()->h;
	}
}

/// <summary>
/// Use the SpriteManager to draw the sprite
/// Chooses which sprite to draw by using the sprites ID assigned to it at creation
/// </summary>
void SDLGameObject::drawObject()
{
	// Reassemble SDL_Rect structure
	m_objectAttributes.x = static_cast<int>(m_position.getX());
	m_objectAttributes.y = static_cast<int>(m_position.getY());
	m_objectAttributes.w = m_objectWidth;
	m_objectAttributes.h = m_objectHeight;

	TheSpriteManager::Instance()->drawSpriteFrame(
		m_objectTextureID,
		m_objectAttributes,
		m_currentSpriteFrame,
		m_bFlipImage,
		m_spriteRotation);
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

