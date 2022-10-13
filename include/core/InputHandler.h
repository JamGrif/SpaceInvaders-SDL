#pragma once

// To use InputHandler you will need enums in Keycodes.h
#include "misc/Keycodes.h"

union SDL_Event;

/// <summary>
/// Encapsulates all input devices, handling any events generated from them
/// </summary>
class InputHandler
{
public:
	bool		init();
	void		update();
	void		clean();

	bool		isMouseButtonDown(int mouseButton) const { return m_mouseButtonStates[mouseButton]; }

	bool		isKeyDown(Keyboard::Keys keyboardKey) const;

	Vector2D	getMousePosition() const { return m_mousePosition; }

	static InputHandler* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new InputHandler();
		return s_pInstance;
	}

private:
	static InputHandler* s_pInstance;

	// Handle Keyboard events
	void		onKeyDown();
	void		onKeyUp();

	// Handle mouse events
	void		onMouseMove(SDL_Event& event);
	void		onMouseButtonDown(SDL_Event& event);
	void		onMouseButtonUp(SDL_Event& event);

	// Current state of the mouse buttons
	std::vector<bool> m_mouseButtonStates;

	// Current mouse position
	Vector2D	m_mousePosition;

	// Current state of the keyboard buttons
	uint8_t*	m_keystates;

	InputHandler();										// Prevent outside unwanted construction
	InputHandler(const InputHandler&);					// Prevent construction by copying
	InputHandler& operator=(const InputHandler&) {};	// Prevent assignment
	~InputHandler() {};									// Prevent outside unwanted destruction

};
typedef InputHandler TheInputHandler;
