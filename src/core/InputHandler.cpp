#include "pch.h"
#include "core/InputHandler.h"

#include "core/Game.h"

InputHandler* InputHandler::s_pInstance = nullptr;

void InputHandler::init()
{
	// Set all mouse button states to false (not pressed)
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

void InputHandler::update()
{
	// Called each frame to update the event state
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				TheGame::Instance()->quit();
				break;

			case SDL_MOUSEMOTION:
				onMouseMove(event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				onMouseButtonDown(event);
				break;

			case SDL_MOUSEBUTTONUP:
				onMouseButtonUp(event);
				break;

			case SDL_KEYDOWN:
				onKeyDown();
				break;

			case SDL_KEYUP:
				onKeyUp();
				break;

			default:
				break;
		}
	}
}

void InputHandler::clean()
{
}

bool InputHandler::isMouseButtonDown(int mouseButton)
{
	return m_mouseButtonStates[mouseButton];
}

Vector2D InputHandler::getMousePosition()
{
	return m_mousePosition;
}

bool InputHandler::isKeyDown(int keyboardKey)
{
	if (m_keystates)
	{
		return m_keystates[keyboardKey] ? true : false;
	}

	return false;
}

InputHandler* InputHandler::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new InputHandler();
	}

	return s_pInstance;
}

InputHandler::InputHandler()
	:m_mousePosition(0,0), m_keystates(0)
{
}


void InputHandler::onKeyDown()
{
	m_keystates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
}

void InputHandler::onKeyUp()
{
	m_keystates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
}

void InputHandler::onMouseMove(SDL_Event& event)
{
	m_mousePosition.setX(static_cast<float>(event.motion.x));
	m_mousePosition.setY(static_cast<float>(event.motion.y));
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		m_mouseButtonStates[Mouse::LEFT] = true;

	if (event.button.button == SDL_BUTTON_MIDDLE)
		m_mouseButtonStates[Mouse::MIDDLE] = true;
	
	if (event.button.button == SDL_BUTTON_RIGHT)
		m_mouseButtonStates[Mouse::RIGHT] = true;
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		m_mouseButtonStates[Mouse::LEFT] = false;

	if (event.button.button == SDL_BUTTON_MIDDLE)
		m_mouseButtonStates[Mouse::MIDDLE] = false;
	
	if (event.button.button == SDL_BUTTON_RIGHT)
		m_mouseButtonStates[Mouse::RIGHT] = false;
}

