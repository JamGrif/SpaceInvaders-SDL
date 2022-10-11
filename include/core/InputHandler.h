#pragma once

// To use InputHandler you will need enums in Keycodes.h
#include "misc/Keycodes.h"

union SDL_Event;

class InputHandler
{
public:
	bool init();
	void update();
	void clean();

	bool isMouseButtonDown(int mouseButton) const { return m_mouseButtonStates[mouseButton]; }

	bool isKeyDown(int keyboardKey) const;

	Vector2D getMousePosition() const { return m_mousePosition; }

	static InputHandler* Instance()
	{
		if (!s_pInstance)
			s_pInstance = new InputHandler();
		return s_pInstance;
	}

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
	uint8_t* m_keystates;

};
typedef InputHandler TheInputHandler;
