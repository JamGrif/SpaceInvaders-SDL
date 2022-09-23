#include "SDLWindow.h"

#include "SDL.h"

#include <iostream>

SDLWindow* SDLWindow::s_pInstance = nullptr;

SDLWindow::SDLWindow()
	:m_pWindow(nullptr), m_windowWidth(0), m_windowHeight(0), m_bStatus(false)
{	
}

void SDLWindow::init(int width, int height)
{
	m_pWindow = SDL_CreateWindow("Jamie", 100, 100, width, height, NULL);
	if (!m_pWindow)
	{
		m_bStatus = false;
		return;
	}

	setWindowIcon("res/misc/icon.bmp");

	m_windowWidth = width;
	m_windowHeight = height;

	m_bStatus = true;
}

void SDLWindow::clean()
{
	SDL_DestroyWindow(m_pWindow);
}

void SDLWindow::setWindowIcon(const char* filepath)
{
	SDL_Surface* tempSurface = SDL_LoadBMP(filepath);
	SDL_SetWindowIcon(m_pWindow, tempSurface);
	SDL_FreeSurface(tempSurface);
}

SDL_Window* SDLWindow::getWindowPtr() const
{
	return m_pWindow;
}

int SDLWindow::getWindowWidth() const
{
	return m_windowWidth;
}

int SDLWindow::getWindowHeight() const
{
	return m_windowHeight;
}

bool SDLWindow::getStatus() const
{
	return m_bStatus;
}

SDLWindow* SDLWindow::Instance()
{
	if (!s_pInstance)
	{
		std::cout << "Creating first instance of SDLWindow" << std::endl;
		s_pInstance = new SDLWindow();
		return s_pInstance;
	}
	return s_pInstance;
}
