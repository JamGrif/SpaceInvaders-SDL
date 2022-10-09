#include "pch.h"
#include "gameobjects/CheckboxButton.h"

#include "core/InputHandler.h"

enum CheckBoxButtonState
{
	FILLED = 0,
	NOT_FILLED = 1,
};

CheckboxButton::CheckboxButton()
	:m_bTicked(true), m_checkboxStateCallback(0), m_checkboxStateCallbackID(0), m_bInitialStateSet(false)
{

}

CheckboxButton::~CheckboxButton()
{

}

void CheckboxButton::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	Button::loadObject(pParams);

	m_checkboxStateCallbackID = pParams->checkboxStateCallbackID;
}

void CheckboxButton::drawObject()
{
	Button::drawObject();
}

void CheckboxButton::updateObject()
{
	// Get coordinates of the mouse pointer
	Vector2D pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (!m_bInitialStateSet)
	{
		m_bInitialStateSet = true;
		m_bTicked = m_checkboxStateCallback();
	}

	m_currentSpriteFrame = m_bTicked ? FILLED : NOT_FILLED;


	// Check if mouse is within the bounds of the button
	if (pMousePos.getX() < (m_position.getX() + m_objectWidth)
		&& pMousePos.getX() > m_position.getX()
		&& pMousePos.getY() < (m_position.getY() + m_objectHeight)
		&& pMousePos.getY() > m_position.getY())
	{
		// Moused over and clicked button
		if (TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT)
			&& m_bReleased)
		{

			m_selectCallback(); // Call the callback function

			m_bTicked = !m_bTicked;
			m_bReleased = false; // Uses this value to ensure we release the mouse button before doing the callback again.

		}
		else if (!TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT))
		{
			m_bReleased = true;
		}
	}
}
