#include "pch.h"
#include "core/Renderer.h"

#include "SDL.h"

#include "core/Window.h"

Renderer* Renderer::s_pInstance = nullptr;

static int backgroundColour[3] = { 255, 100, 75 };

Renderer::Renderer()
	:m_pRenderer(nullptr), m_bStatus(false)
{
	
}

void Renderer::init()
{
	// 2nd parameter is the index of the rendering driver to initialize (-1 to use first capable driver)
	// 3rd parameter are the SDL__RendererFlag
	m_pRenderer = SDL_CreateRenderer(TheWindow::Instance()->getWindowPtr(), -1, 0);

	// Check renderer status
	if (!m_pRenderer)
	{
		m_bStatus = false;
		return;
	}

	SDL_SetRenderDrawColor(m_pRenderer, backgroundColour[0], backgroundColour[1], backgroundColour[2], SDL_ALPHA_OPAQUE);

	m_bStatus = true;
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

void Renderer::draw()
{

}

void Renderer::EndOfFrame()
{
	// Show the window
	SDL_RenderPresent(m_pRenderer);
}

SDL_Renderer* Renderer::getRendererPtr() const
{
	return m_pRenderer;
}

bool Renderer::getStatus() const
{
	return m_bStatus;
}

Renderer* Renderer::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new Renderer();
		return s_pInstance;
	}
	return s_pInstance;
}
