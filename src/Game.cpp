#include "pch.h"
#include "Game.h"

#include "GameStateMachine.h"

#include "Window.h"
#include "Renderer.h"
#include "InputHandler.h"

#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "MainMenuState.h" 
#include "Enemy.h"
#include "Player.h"
#include "AnimatedGraphic.h"

Game* Game::s_pInstance = 0;

constexpr int FPS = 60;
constexpr int DELAY_TIME = 1000.0f / FPS; // Gives the amount of time we need to delay the game between loops to keep the frame rate constant. (1000 = number of milliseconds in a second)
Uint32 frameStart, frameTime;

Game::Game()
	:m_pGameStateMachine(nullptr), m_bRunning(false)
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

	TheWindow::Instance()->init(640, 480);
	if (!TheWindow::Instance()->getStatus())
		return false; // Window creation failed

	TheRenderer::Instance()->init();
	if (!TheRenderer::Instance()->getStatus())
		return false; // Renderer creation failed

	TheInputHandler::Instance()->init();

	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->pushState(new MainMenuState());


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
}

void Game::clean()
{
	TheInputHandler::Instance()->clean();
	TheRenderer::Instance()->clean();
	TheWindow::Instance()->clean();
	SDL_Quit();
}

/// <summary>
/// Makes the game end at the start of the next frame
/// </summary>
void Game::quit()
{
	m_bRunning = false;
}

Game* Game::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new Game();
	}
	return s_pInstance;
}
