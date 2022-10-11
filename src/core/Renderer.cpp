#include "pch.h"
#include "core/Renderer.h"

#include "SDL2/SDL.h"

#include "core/Window.h"

Renderer* Renderer::s_pInstance = nullptr;


#define BLACK 0
#define WHITE 255

Renderer::Renderer()
	:m_pRenderer(nullptr)
{
}

bool Renderer::init()
{
	// 2nd parameter is the index of the rendering driver to initialize (-1 to use first capable driver)
	// 3rd parameter are the SDL__RendererFlag
	m_pRenderer = SDL_CreateRenderer(TheWindow::Instance()->getWindowPtr(), -1, 0);
	if (!m_pRenderer)
		return false;
	
	SDL_SetRenderDrawColor(m_pRenderer, BLACK, BLACK, BLACK, SDL_ALPHA_OPAQUE);

	return true;
}

void Renderer::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
}

void Renderer::startOfFrame()
{
	// Clear the window
	SDL_RenderClear(m_pRenderer);
}

//void Renderer::draw()
//{
//}

void Renderer::EndOfFrame()
{
	// Show the window
	SDL_RenderPresent(m_pRenderer);
}

