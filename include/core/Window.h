#pragma once

struct SDL_Window;

/// <summary>
/// Encapsulates the SDL_Window structure and provides utility functions for it
/// </summary>
class Window
{
public:

	bool init(std::string windowTitle, int width, int height);
	void clean();

	SDL_Window* getWindowPtr() const { return m_pWindow; }

	int getWindowWidth() const { return m_windowWidth; };
	int getWindowHeight() const { return m_windowHeight; };

	static Window* Instance() // Singleton
	{
		if (!s_pInstance)
			s_pInstance = new Window();
		return s_pInstance;
	}

private:
	Window();
	static Window* s_pInstance;

	SDL_Window* m_pWindow;

	int m_windowWidth;
	int m_windowHeight;

};
typedef Window TheWindow;
