#include "pch.h"
#include "gameobjects/ClickButton.h"

#include "core/InputHandler.h"

enum MenuButtonState
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
}; 

ClickButton::ClickButton()
	:Button()
{
}

ClickButton::~ClickButton()
{
}

/// <summary>
/// Set all values in ClickButton and parent classes
/// </summary>
void ClickButton::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	Button::loadObject(pParams);

	m_currentSpriteFrame = MOUSE_OUT;
}

/// <summary>
/// Call parent class draw function
/// </summary>
void ClickButton::drawObject()
{
	Button::drawObject();
}

/// <summary>
/// Update values used in this class
/// </summary>
void ClickButton::updateObject()
{
	// Get coordinates of the mouse pointer
	Vector2D pMousePos = TheInputHandler::Instance()->getMousePosition();

	// Check if mouse is within bounds of the button
	if (pMousePos.getX() < (m_position.getX() + m_objectWidth)
		&& pMousePos.getX() > m_position.getX()
		&& pMousePos.getY() < (m_position.getY() + m_objectHeight)
		&& pMousePos.getY() > m_position.getY())
	{
		m_currentSpriteFrame = MOUSE_OVER;

		// Moused over and clicked button
		if (TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT)
			&& m_bReleased)
		{
			m_currentSpriteFrame = CLICKED;

			// Call the callback function
			m_selectCallback(); 

			//  Value ensured mouse is released before calling callback function again
			m_bReleased = false; 
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
	}
}
