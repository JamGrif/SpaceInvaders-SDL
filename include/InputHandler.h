#pragma once

#include "SDL.h"
#include <vector>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:

	void update();
	void clean();

	void initJoysticks();
	bool joysticksInitialized() { return m_bJoysticksInitialized; }
	int xValue(int joy, int stick); // joy is the ID of the joystick to use and stick is 1 for left stick and 2 for right stick
	int yValue(int joy, int stick);

	// Grab the current button state from the specified joystick
	bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	bool getMouseButtonState(int buttonNumber)
	{
		return m_mouseButtonStates[buttonNumber];
	}

	Vector2D getMousePosition()
	{
		return m_mousePosition;
	}

	bool isKeyDown(SDL_Scancode key);



	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}
private:
	InputHandler();
	~InputHandler();

	static InputHandler* s_pInstance;

	// 
	// Handle Keyboard events
	void onKeyDown();
	void onKeyUp();

	// Handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// Handle Joysticks events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	// Joysticks General
	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialized;

	// Joystick Axis
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	const int m_joystickDeadZone = 10000; // Used to account for sensitivity of a controller.

	//Joystick Buttons
	std::vector<std::vector<bool>> m_buttonStates; // First index is each controller and second index is each button on that controller

	// Mouse Buttons
	std::vector<bool> m_mouseButtonStates;

	// Mouse motion
	Vector2D m_mousePosition;

	// Keyboard Button
	Uint8* m_keystates;

};
typedef InputHandler TheInputHandler;
