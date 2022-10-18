#include "pch.h"
#include "core/InputHandler.h"

#include "SDL2/SDL.h"

#include "core/Game.h"

InputHandler* InputHandler::s_pInstance = nullptr;

/// <summary>
/// Initializes the InputHandler systems
/// </summary>
bool InputHandler::init()
{
	m_mouseButtonStates.resize(4);

	// Set all mouse button states to false (not pressed)
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}

	return true;
}

/// <summary>
/// Check and handle events from the mouse and keyboard
/// Called every frame
/// </summary>
void InputHandler::update()
{
	SDL_Event event;

	// Deal with any events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				std::cout << "quit" << std::endl;
				TheGame::Instance()->quitGame();
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

/// <summary>
/// Clean up the InputHandler systems
/// </summary>
void InputHandler::clean()
{
}

/// <summary>
/// See if specified keyboard key is pressed down
/// </summary>
bool InputHandler::isKeyDown(Keyboard::Keys keyboardKey) const
{
	if (m_keystates)
		return m_keystates[keyboardKey] ? true : false;
	
	return false;
}

/// <summary>
/// Update the current state of the keyboard
/// Called when a key press event has been made
/// </summary>
void InputHandler::onKeyDown()
{
	m_keystates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
}

/// <summary>
/// Update the current state of the keyboard
/// Called when a key press event has been made
/// </summary>
void InputHandler::onKeyUp()
{
	m_keystates = const_cast<Uint8*>(SDL_GetKeyboardState(0));
}

/// <summary>
/// Update the current mouse's position
/// Called when a mouse movement event has been made
/// </summary>
void InputHandler::onMouseMove(SDL_Event& event)
{
	m_mousePosition.setX(static_cast<float>(event.motion.x));
	m_mousePosition.setY(static_cast<float>(event.motion.y));
}

/// <summary>
/// Update which mouse button is pressed down
/// Called when a mouse button event has been made
/// </summary>
void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == Mouse::Buttons::LEFT)
		m_mouseButtonStates.at(Mouse::LEFT) = true;

	if (event.button.button == Mouse::Buttons::MIDDLE)
		m_mouseButtonStates.at(Mouse::MIDDLE) = true;
	
	if (event.button.button == Mouse::Buttons::RIGHT)
		m_mouseButtonStates.at(Mouse::RIGHT) = true;
	
}

/// <summary>
/// Update which mouse button is no longer pressed
/// Called when a mouse button event has been made
/// </summary>
void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == Mouse::Buttons::LEFT)
		m_mouseButtonStates.at(Mouse::LEFT) = false;

	if (event.button.button == Mouse::Buttons::MIDDLE)
		m_mouseButtonStates.at(Mouse::MIDDLE) = false;
	
	if (event.button.button == Mouse::Buttons::RIGHT)
		m_mouseButtonStates.at(Mouse::RIGHT) = false;
}

InputHandler::InputHandler()
	:m_mousePosition(0, 0), m_keystates(0)
{
}
