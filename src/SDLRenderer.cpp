#include "SDLRenderer.h"

#include "SDLWindow.h"

#include <SDL.h>

#include <iostream>

static int backgroundColour[3] = { 255, 100, 75 };

SDLRenderer* SDLRenderer::s_pInstance = nullptr;

SDLRenderer::SDLRenderer()
	:m_pRenderer(nullptr), m_bStatus(false)
{
	
}

void SDLRenderer::init()
{
	// 2nd parameter is the index of the rendering driver to initialize (-1 to use first capable driver)
	// 3rd parameter are the SDL__RendererFlag
	m_pRenderer = SDL_CreateRenderer(SDLWindow::Instance()->getWindowPtr(), -1, 0);

	// Check renderer status
	if (!m_pRenderer)
	{
		m_bStatus = false;
		return;
	}

	SDL_SetRenderDrawColor(m_pRenderer, backgroundColour[0], backgroundColour[1], backgroundColour[2], SDL_ALPHA_OPAQUE);

	m_bStatus = true;
}

void SDLRenderer::clean()
{
	SDL_DestroyRenderer(m_pRenderer);
}

void SDLRenderer::startOfFrame()
{
	// Clear the window
	SDL_RenderClear(m_pRenderer);
}

void SDLRenderer::draw()
{

}

void SDLRenderer::EndOfFrame()
{
	// Show the window
	SDL_RenderPresent(m_pRenderer);
}

SDL_Renderer* SDLRenderer::getRendererPtr() const
{
	return m_pRenderer;
}

bool SDLRenderer::getStatus() const
{
	return m_bStatus;
}

SDLRenderer* SDLRenderer::Instance()
{
	if (!s_pInstance)
	{
		std::cout << "Creating first instance of SDLRenderer" << std::endl;
		s_pInstance = new SDLRenderer();
		return s_pInstance;
	}
	return s_pInstance;
}
