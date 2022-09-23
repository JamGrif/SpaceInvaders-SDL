#include "InputHandler.h"

#include <iostream>

#include "Game.h"

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

			case SDL_JOYAXISMOTION:
				onJoystickAxisMove(event);
				break;

			case SDL_JOYBUTTONDOWN:
				onJoystickButtonDown(event);
				break;

			case SDL_JOYBUTTONUP:
				onJoystickButtonUp(event);
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
	// Loop through the SDL_Joystick* vector and close each one
	if (m_bJoysticksInitialized)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

void InputHandler::initJoysticks()
{

	// Check if subsystem has been enabled
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
		// Open each available joystick and, if valid, add them to the vector of available joysticks
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (joy)
			{
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0,0))); // Add the joystick pair

				// Init all buttons for the controller
				std::vector<bool> tempButtons;
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}

				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				std::cout << SDL_GetError() << std::endl;;
			}
		}

		// Tell SDL to start listening for joystick events
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialized = true;

		std::cout << "Initialized " << m_joysticks.size() << " joystick(s)" << std::endl;
	}
	else
	{
		m_bJoysticksInitialized = false;
	}

}

int InputHandler::xValue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getX();
		}
	}

	return 0;
}

int InputHandler::yValue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getY();
		}
	}

	return 0;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

InputHandler::InputHandler()
	:m_mousePosition(0,0)
{
	// Set all mouse button states to false (not pressed)
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

InputHandler::~InputHandler()
{

}

InputHandler* InputHandler::s_pInstance;

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
	m_mousePosition.setX(event.motion.x);
	m_mousePosition.setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
	int whichOne = event.jaxis.which; // Determine which controller had the input
	// m_joystickValues[whichone] too ensure we select the correct controller

	/*
		.axis ==
		0 - left/right movement on stick one (left stick)
		1 - up/down movement on stick one	 (left stick)
		3 - left/right movement on stick two (right stick)
		4 - up/down movement on stick two	 (right stick)
	*/

	// Left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}

	// Left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}

	// Right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setX(0);
		}
	}

	// Right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setY(0);
		}
	}

}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
	int whichOne = event.jaxis.which; // j prefix is for joystick
	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = false;
}
