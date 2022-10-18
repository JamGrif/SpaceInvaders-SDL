#pragma once

struct SDL_Window;

/// <summary>
/// Encapsulates the SDL_Window structure and provides utility functions for it
/// </summary>
class GameWindow
{
public:
	bool			init(const std::string& windowTitle, int width, int height);
	void			clean();

	SDL_Window*		getWindowPtr() const { return m_pWindow; }

	int				getWindowWidth() const { return m_windowWidth; };
	int				getWindowHeight() const { return m_windowHeight; };

	static GameWindow*	Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new GameWindow();
		return s_pInstance;
	}

private:
	static GameWindow* s_pInstance;

	SDL_Window* m_pWindow;

	int m_windowWidth;
	int m_windowHeight;

	GameWindow() :m_pWindow(nullptr), m_windowWidth(0), m_windowHeight(0) {};				// Prevent outside unwanted construction
	GameWindow(const GameWindow&) :m_pWindow(nullptr), m_windowWidth(0), m_windowHeight(0) {};	// Prevent construction by copying
	GameWindow& operator=(const GameWindow&) {};												// Prevent assignment
	~GameWindow() {};																		// Prevent outside unwanted destruction

};
typedef GameWindow TheGameWindow;
