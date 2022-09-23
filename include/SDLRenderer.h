#pragma once

#include <iostream>

// Forward Declaration
struct SDL_Renderer;

/// <summary>
/// Encapsulates the SDL_Renderer structure and provides utility functions for it
/// </summary>
class SDLRenderer
{
public:
	void init();
	void clean();

	void startOfFrame();
	void draw();
	void EndOfFrame();

	SDL_Renderer* getRendererPtr() const;

	bool getStatus() const;

	static SDLRenderer* Instance(); // Singleton
private:
	SDLRenderer();
	static SDLRenderer* s_pInstance;

	SDL_Renderer* m_pRenderer;

	bool m_bStatus;
};
typedef SDLRenderer TheRenderer;

