#pragma once

namespace Mouse
{
	enum Buttons
	{
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
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
