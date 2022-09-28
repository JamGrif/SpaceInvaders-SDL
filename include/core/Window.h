#pragma once

// Forward Declaration
struct SDL_Window;

/// <summary>
/// Encapsulates the SDL_Window structure and provides utility functions for it
/// </summary>
class Window
{
public:

	void init(int width, int height);
	void clean();

	inline void setWindowIcon(const std::string& filepath);

	SDL_Window* getWindowPtr() const;

	int getWindowWidth() const;
	int getWindowHeight() const;

	bool getStatus() const;

	static Window* Instance(); // Singleton
private:
	Window();
	static Window* s_pInstance;

	SDL_Window* m_pWindow;

	int m_windowWidth;
	int m_windowHeight;

	bool m_bStatus;
};
typedef Window TheWindow;
