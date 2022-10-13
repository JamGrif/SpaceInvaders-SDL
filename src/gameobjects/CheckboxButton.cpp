#include "pch.h"
#include "gameobjects/CheckboxButton.h"

#include "core/InputHandler.h"

enum CheckBoxButtonState
{
	FILLED					= 0,
	NOT_FILLED				= 1,
	FILLED_HIGHLIGHT		= 2,
	NOT_FILLED_HIGHLIGHT	= 3
};

CheckboxButton::CheckboxButton()
	:m_bTicked(true), m_checkboxStateCallback(0), m_checkboxStateCallbackID(0), m_bInitialStateSet(false)
{
}

CheckboxButton::~CheckboxButton()
{
}

/// <summary>
/// Set all values in CheckboxButton and parent classes
/// </summary>
void CheckboxButton::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	Button::loadObject(pParams);

	m_checkboxStateCallbackID = pParams->checkboxStateCallbackID;
}

/// <summary>
/// Call parent class draw function
/// </summary>
void CheckboxButton::drawObject()
{
	Button::drawObject();
}

/// <summary>
/// Update values used in this class
/// </summary>
void CheckboxButton::updateObject()
{
	// Get coordinates of the mouse pointer
	Vector2D pMousePos = TheInputHandler::Instance()->getMousePosition();

	// If first time, set state of the checkbox (ticked or not)
	if (!m_bInitialStateSet)
	{
		m_bInitialStateSet = true;
		m_bTicked = m_checkboxStateCallback();
	}

	// Check if mouse is within bounds of the button
	if (pMousePos.getX() < (m_position.getX() + m_objectWidth)
		&& pMousePos.getX() > m_position.getX()
		&& pMousePos.getY() < (m_position.getY() + m_objectHeight)
		&& pMousePos.getY() > m_position.getY())
	{
		m_currentSpriteFrame = m_bTicked ? FILLED_HIGHLIGHT : NOT_FILLED_HIGHLIGHT;

		// Moused over and clicked button
		if (m_bReleased &&
			TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT))
		{
			// Call the callback function
			m_selectCallback();

			m_bTicked = !m_bTicked;

			// Value ensured mouse is released before calling callback function again
			m_bReleased = false; 
		}
		else if (!TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT))
		{
			m_bReleased = true;
		}
	}
	else
	{
		m_currentSpriteFrame = m_bTicked ? FILLED : NOT_FILLED;
	}
}
