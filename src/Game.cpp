#include "Game.h"
//#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "InputHandler.h"

#include "MenuState.h"
#include "PlayState.h"

Game* Game::s_pInstance = 0;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS; // Gives the amount of time we need to delay the game between loops to keep the frame rate constant. (1000 = number of milliseconds in a second)
Uint32 frameStart, frameTime;

Game::Game()
	:m_bRunning(false)
{
}

bool Game::init()
{
	// Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL could not init" << std::endl;
		return false;
	}

	SDLWindow::Instance()->init(640, 480);
	if (!SDLWindow::Instance()->getStatus())
		return false; // Window creation failed

	TheRenderer::Instance()->init();
	if (!TheRenderer::Instance()->getStatus())
		return false; // Renderer creation failed
	
	if (!TheTextureManager::Instance()->load("res/sprites/animate-alpha.png", "animate", TheRenderer::Instance()->getRendererPtr()))
		return false; // Texture failed to load

	TheInputHandler::Instance()->init();

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());

	m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

	m_bRunning = true;
	return true;
}

// SDL_GetTicks() returns the amount of milliseconds since SDL_Init was called
void Game::loop()
{
	while (m_bRunning)
	{
		frameStart = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - frameStart; // Stores how long it took for frame to run

		if (frameTime < DELAY_TIME) // If it is less than the time we want a frame to take, we call SDL_Delay to make the loop wait for the amount of time we want, subtracting how long the loop already took to complete
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
}

void Game::render()
{
	TheRenderer::Instance()->startOfFrame();

	m_pGameStateMachine->render();

	TheRenderer::Instance()->EndOfFrame();
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::ENTER))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}

	if (TheInputHandler::Instance()->isKeyDown(Keyboard::BACKSPACE))
	{
		m_pGameStateMachine->changeState(new MenuState());
	}
}

void Game::clean()
{
	TheInputHandler::Instance()->clean();
	TheRenderer::Instance()->clean();
	SDLWindow::Instance()->clean();
	SDL_Quit();
}

void Game::quit()
{
	m_bRunning = false;
}

bool Game::getRunning()
{
	return m_bRunning;
}

Game* Game::Instance()
{
	std::cout << "got game instance" << std::endl;
	if (s_pInstance == 0)
	{
		std::cout << "Created new instance of game" << std::endl;
		s_pInstance = new Game();
		return s_pInstance;
	}
	return s_pInstance;
}
