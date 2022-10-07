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

	SDL_Renderer* getRendererPtr() const { return m_pRenderer; }

	static Renderer* Instance() // Singleton
	{
		if (!s_pInstance)
			s_pInstance = new Renderer();
		return s_pInstance;
	}
private:
	Renderer();
	static Renderer* s_pInstance;

	SDL_Renderer* m_pRenderer;
};
typedef Renderer TheRenderer;

