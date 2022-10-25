#pragma once

struct SDL_Window;

/// <summary>
/// Encapsulates the SDL_Window structure and provides utility functions for it
/// </summary>
class GameWindow
{
public:
	bool				init(const std::string& windowTitle, uint16_t width, uint16_t height);
	void				clean();

	SDL_Window*			getWindowPtr() const { return m_pWindow; }

	uint16_t			getWindowWidth() const { return m_windowWidth; };
	uint16_t			getWindowHeight() const { return m_windowHeight; };

	static GameWindow*	Instance() // Get instance
	{
		static GameWindow* s_pInstance = new GameWindow;
		return s_pInstance;
	}

private:

	SDL_Window*			m_pWindow;

	uint16_t			m_windowWidth;
	uint16_t			m_windowHeight;

	GameWindow() :m_pWindow(nullptr), m_windowWidth(0), m_windowHeight(0) {};	// Prevent outside unwanted construction
	GameWindow(const GameWindow&) = delete;										// Prevent construction by copying
	GameWindow& operator=(const GameWindow&) = delete;							// Prevent assignment
	~GameWindow() {};															// Prevent outside unwanted destruction

};
typedef GameWindow TheGameWindow;
