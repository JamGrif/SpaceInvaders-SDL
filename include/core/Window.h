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

	SDL_Window* getWindowPtr() const;

	int getWindowWidth() const;
	int getWindowHeight() const;

	static Window* Instance(); // Singleton
private:
	Window();
	static Window* s_pInstance;

	SDL_Window* m_pWindow;

	int m_windowWidth;
	int m_windowHeight;

};
typedef Window TheWindow;
