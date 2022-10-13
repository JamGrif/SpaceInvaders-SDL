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
	void EndOfFrame();

	SDL_Renderer* getRendererPtr() const { return m_pRenderer; }

	static Renderer* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new Renderer();
		return s_pInstance;
	}
private:

	static Renderer* s_pInstance;

	SDL_Renderer* m_pRenderer;

	Renderer();									// Prevent outside unwanted construction
	Renderer(const Renderer&) :m_pRenderer(nullptr) {};				// Prevent construction by copying
	Renderer& operator=(const Renderer&) {};	// Prevent assignment
	~Renderer() {};								// Prevent outside unwanted destruction
};
typedef Renderer TheRenderer;

