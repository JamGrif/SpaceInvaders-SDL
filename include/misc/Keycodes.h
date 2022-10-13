#pragma once

namespace Mouse
{
	// Numbers from SDL_mouse.h
	enum Buttons
	{
		LEFT = 1,
		MIDDLE = 2,
		RIGHT = 3
	};
}

namespace Keyboard
{
	// Numbers from SDL_scancode.h
	enum Keys
	{
		W = 26,
		A = 4,
		D = 7,
		S = 22,

		ONE = 30,

		ENTER = 40,
		BACKSPACE = 42,
		ESC = 41,
		SPACE = 44,

		UP_ARROW = 82,
		DOWN_ARROW = 81,
		RIGHT_ARROW = 79,
		LEFT_ARROW = 80
	};
}
