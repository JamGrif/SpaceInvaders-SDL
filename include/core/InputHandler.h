#pragma once

#include "SDL.h"

namespace Mouse
{
	enum Buttons // Mouse buttons
	{
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
	};
}

namespace Keyboard
{
	enum Keys // Keyboard keys
	{
		W = SDL_SCANCODE_W,
		A = SDL_SCANCODE_A,
		D = SDL_SCANCODE_D,
		S = SDL_SCANCODE_S,

		ENTER = SDL_SCANCODE_RETURN,
		BACKSPACE = SDL_SCANCODE_BACKSPACE,
		ESC = SDL_SCANCODE_ESCAPE,

		UP_ARROW = SDL_SCANCODE_UP,
		DOWN_ARROW = SDL_SCANCODE_DOWN,
		RIGHT_ARROW = SDL_SCANCODE_RIGHT,
		LEFT_ARROW = SDL_SCANCODE_LEFT
	};
}


class InputHandler
{
public:
	void init();
	void update();
	void clean();

	bool isMouseButtonDown(int mouseButton);
	bool isKeyDown(int keyboardKey);
	Vector2D getMousePosition();

	static InputHandler* Instance();
private:
	InputHandler();
	static InputHandler* s_pInstance;

	// Handle Keyboard events
	void onKeyDown();
	void onKeyUp();

	// Handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// Mouse Buttons
	std::vector<bool> m_mouseButtonStates;

	// Mouse motion
	Vector2D m_mousePosition;

	// Keyboard Buttons
	Uint8* m_keystates;

};
typedef InputHandler TheInputHandler;
