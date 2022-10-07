#include "pch.h"
#include "gameobjects/MenuButton.h"

#include "core/InputHandler.h"
#include "core/SoundManager.h"

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
}; 

MenuButton::MenuButton()
	:SDLGameObject(), m_bReleased(false), m_callback(0), m_callbackID(0), m_bPlayedSound(false)
{
}

MenuButton::~MenuButton()
{
}

/// <summary>
/// Responsible for setting all variables used in MenuButton and inherited class
/// </summary>
/// <param name="pParams"></param>
void MenuButton::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_callbackID = pParams->callbackID;
	m_currentSpriteFrame = MOUSE_OUT;
}

void MenuButton::drawObject()
{
	SDLGameObject::drawObject();
}

void MenuButton::updateObject()
{
	// Get coordinates of the mouse pointer
	Vector2D pMousePos = TheInputHandler::Instance()->getMousePosition();

	// Check if mouse is within the bounds of the button
	if (pMousePos.getX() < (m_position.getX() + m_objectWidth)
		&& pMousePos.getX() > m_position.getX()
		&& pMousePos.getY() < (m_position.getY() + m_objectHeight)
		&& pMousePos.getY() > m_position.getY())
	{
		m_currentSpriteFrame = MOUSE_OVER;

		if (!m_bPlayedSound)
		{
			//TheSoundManager::Instance()->playSound("menuMouseOver");
			m_bPlayedSound = true;
		}
			

		// Moused over and clicked button
		if (TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT)
			&& m_bReleased)
		{
			m_currentSpriteFrame = CLICKED;

			m_callback(); // Call the callback function

			m_bReleased = false; // Uses this value to ensure we release the mouse button before doing the callback again.

			
		}
		else if (!TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT))
		{
			m_bReleased = true;
			m_currentSpriteFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentSpriteFrame = MOUSE_OUT;
		m_bPlayedSound = false;
	}
}
