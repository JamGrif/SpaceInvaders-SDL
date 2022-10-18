#include "pch.h"
#include "core/GameWindow.h"

#include "SDL2/SDL.h"

GameWindow* GameWindow::s_pInstance = nullptr;

/// <summary>
/// Initializes the Window systems
/// </summary>
bool GameWindow::init(const std::string& windowTitle, int width, int height)
{
	m_pWindow = SDL_CreateWindow(windowTitle.c_str(), width/2, height/4, width, height, NULL);
	if (!m_pWindow)
		return false;

	m_windowWidth = width;
	m_windowHeight = height;

	return true;
}

/// <summary>
/// Clean up the Window systems
/// </summary>
void GameWindow::clean()
{
	SDL_DestroyWindow(m_pWindow);
}
