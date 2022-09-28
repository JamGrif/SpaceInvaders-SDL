#include "pch.h"
#include "MenuButton.h"

#include "InputHandler.h"

MenuButton::MenuButton()
	:SDLGameObject(), m_bReleased(false), m_callback(0), m_callbackID(0)
{
	m_currentFrame = MOUSE_OUT; // Start at frame 0
}

void MenuButton::draw()
{
	SDLGameObject::draw(); // Uses base class drawing
}

void MenuButton::update()
{
	// Get coordinates of the mouse pointer
	Vector2D pMousePos = TheInputHandler::Instance()->getMousePosition();

	// Check if mouse is within the bounds of the button
	if (pMousePos.getX() < (m_position.getX() + m_width)
		&& pMousePos.getX() > m_position.getX()
		&& pMousePos.getY() < (m_position.getY() + m_height)
		&& pMousePos.getY() > m_position.getY())
	{
		m_currentFrame = MOUSE_OVER;

		// Moused over and clicked button
		if (TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT)
			&& m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback(); // Call the callback function

			m_bReleased = false; // Uses this value to ensure we release the mouse button before doing the callback again.
		}
		else if (!TheInputHandler::Instance()->isMouseButtonDown(Mouse::LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_callbackID = pParams->getCallBackID();
	m_currentFrame = MOUSE_OUT;
}
