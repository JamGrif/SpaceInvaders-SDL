#include "pch.h"
#include "gameobjects/SDLGameObject.h"

#include "core/SpriteManager.h"
#include "core/Window.h"

SDLGameObject::SDLGameObject()
	:BaseGameObject(), m_position(0, 0), m_velocity(0, 0), m_objectWidth(0), m_objectHeight(0), m_currentSpriteFrame(1), m_bFlipImage(false)
{
}

SDLGameObject::~SDLGameObject()
{
}

/// <summary>
/// Responsible for setting all variables used in SDLGameObject
/// </summary>
void SDLGameObject::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	m_position = Vector2D(static_cast<float>(pParams->xPos), static_cast<float>(pParams->yPos));

	m_objectTextureID = pParams->textureID;
	m_framesInSprite = pParams->numFrames;
	m_animationSpeed = pParams->animationSpeed;
	m_movementSpeed = pParams->movementSpeed;

	m_screenWidth = TheWindow::Instance()->getWindowWidth();
	m_screenHeight = TheWindow::Instance()->getWindowHeight();

	// The Object width and height is the dimensions of the current sprite frame on its sprite sheet
	Sprite* s = TheSpriteManager::Instance()->getSpriteViaID(m_objectTextureID);
	if (s)
	{
		s->setUpIndividualSpriteDimensions(pParams->numFrames);
		m_objectWidth = s->getIndividualDimensions().w;
		m_objectHeight = s->getIndividualDimensions().h;
	}
}

void SDLGameObject::drawObject()
{
	//if (m_velocity.getX() != 0)
	//	m_bFlipImage = m_velocity.getX() > 0 ? true : false;
	
	SpriteManager::Instance()->drawSpriteFrame(
		m_objectTextureID,
		static_cast<int>(m_position.getX()),
		static_cast<int>(m_position.getY()),
		m_objectWidth,
		m_objectHeight,
		m_currentSpriteFrame,
		m_bFlipImage);
}

void SDLGameObject::updateObject()
{
	// Allows gradual increase of velocity through acceleration
	m_position += m_velocity;

	// Set correct sprite frame
	//if (m_framesInSprite > 1)

	m_currentSpriteFrame = static_cast<int>(((SDL_GetTicks() / m_animationSpeed) % m_framesInSprite));
}

