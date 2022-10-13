#pragma once

struct SDL_Window;

/// <summary>
/// Encapsulates the SDL_Window structure and provides utility functions for it
/// </summary>
class Window
{
public:
	bool			init(const std::string& windowTitle, int width, int height);
	void			clean();

	SDL_Window*		getWindowPtr() const { return m_pWindow; }

	int				getWindowWidth() const { return m_windowWidth; };
	int				getWindowHeight() const { return m_windowHeight; };

	static Window*	Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new Window();
		return s_pInstance;
	}

private:
	static Window* s_pInstance;

	SDL_Window* m_pWindow;

	int m_windowWidth;
	int m_windowHeight;

	Window() :m_pWindow(nullptr), m_windowWidth(0), m_windowHeight(0) {};				// Prevent outside unwanted construction
	Window(const Window&) :m_pWindow(nullptr), m_windowWidth(0), m_windowHeight(0) {};	// Prevent construction by copying
	Window& operator=(const Window&) {};												// Prevent assignment
	~Window() {};																		// Prevent outside unwanted destruction

};
typedef Window TheWindow;
