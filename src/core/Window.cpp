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

	m_windowWidth = width;
	m_windowHeight = height;

	return true;
}

void Window::clean()
{
	SDL_DestroyWindow(m_pWindow);
}
