#include "pch.h"
#include "core/Window.h"

#include "SDL2/SDL.h"

Window* Window::s_pInstance = nullptr;

Window::Window()
	:m_pWindow(nullptr), m_windowWidth(0), m_windowHeight(0)
{	
}

bool Window::init(std::string windowTitle, int width, int height)
{
	m_pWindow = SDL_CreateWindow(windowTitle.c_str(), 100, 100, width, height, NULL);
	if (!m_pWindow)
		return false;

	setWindowIcon("res/misc/icon.bmp");

	m_windowWidth = width;
	m_windowHeight = height;

	return true;
}

void Window::clean()
{
	SDL_DestroyWindow(m_pWindow);
}

void Window::setWindowIcon(const std::string& filepath)
{
	SDL_Surface* tempSurface = SDL_LoadBMP(filepath.c_str());
	SDL_SetWindowIcon(m_pWindow, tempSurface);
	SDL_FreeSurface(tempSurface);
}

SDL_Window* Window::getWindowPtr() const
{
	return m_pWindow;
}

int Window::getWindowWidth() const
{
	return m_windowWidth;
}

int Window::getWindowHeight() const
{
	return m_windowHeight;
}

Window* Window::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new Window();
		return s_pInstance;
	}
	return s_pInstance;
}
