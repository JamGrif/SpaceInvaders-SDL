#pragma once

struct SDL_Renderer;

/// <summary>
/// Encapsulates the SDL_Renderer structure and provides utility functions for it
/// </summary>
class Renderer
{
public:
	bool init();
	void clean();

	void startOfFrame();
	void draw();
	void EndOfFrame();

	SDL_Renderer* getRendererPtr() const;

	static Renderer* Instance(); // Singleton
private:
	Renderer();
	static Renderer* s_pInstance;

	SDL_Renderer* m_pRenderer;
};
typedef Renderer TheRenderer;

