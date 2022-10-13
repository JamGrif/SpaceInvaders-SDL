#include "pch.h"
#include "core/Renderer.h"

#include "SDL2/SDL.h"

#include "core/Window.h"

#define BLACK 0
#define WHITE 255

Renderer* Renderer::s_pInstance = nullptr;

/// <summary>
/// Initializes the Renderer systems
/// </summary>
bool Renderer::init()
{
	m_pRenderer = SDL_CreateRenderer(TheWindow::Instance()->getWindowPtr(), -1, 0);
	if (!m_pRenderer)
		return false;
	
	SDL_SetRenderDrawColor(m_pRenderer, BLACK, BLACK, BLACK, SDL_ALPHA_OPAQUE);

	return true;
}

/// <summary>
/// Clean up the Renderer systems
/// </summary>
void Renderer::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
}

/// <summary>
/// Prepares SDL for next frame of rendering
/// </summary>
void Renderer::startOfFrame()
{
	// Clear the window
	SDL_RenderClear(m_pRenderer);
}

/// <summary>
/// Present newly created frame
/// </summary>
void Renderer::EndOfFrame()
{
	// Show the window
	SDL_RenderPresent(m_pRenderer);
}

Renderer::Renderer()
	:m_pRenderer(nullptr)
{
}
