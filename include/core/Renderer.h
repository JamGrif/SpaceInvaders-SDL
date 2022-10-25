#pragma once

struct SDL_Renderer;

/// <summary>
/// Encapsulates the SDL_Renderer structure and provides utility functions for it
/// </summary>
class Renderer
{
public:
	bool			init();
	void			clean();

	void			startOfFrame();
	void			EndOfFrame();

	SDL_Renderer*	getRendererPtr() const { return m_pRenderer; }

	static Renderer* Instance() // Get instance
	{
		static Renderer* s_pInstance = new Renderer;
		return s_pInstance;
	}
private:

	SDL_Renderer*	m_pRenderer;

	Renderer();										// Prevent outside unwanted construction
	Renderer(const Renderer&) = delete;				// Prevent construction by copying
	Renderer& operator=(const Renderer&) = delete;	// Prevent assignment
	~Renderer() {};									// Prevent outside unwanted destruction
};
typedef Renderer TheRenderer;

