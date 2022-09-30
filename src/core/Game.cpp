#include "pch.h"
#include "core/Game.h"

#include "core/Window.h"
#include "core/Renderer.h"
#include "core/InputHandler.h"
#include "gameobjects/MenuButton.h"
#include "gameobjects/Enemy.h"
#include "gameobjects/Player.h"
#include "gameobjects/AnimatedGraphic.h"
#include "gameobjects/utility/GameObjectFactory.h"
#include "states/MainMenuState.h" 
#include "states/utility/GameStateMachine.h"

Game* Game::s_pInstance = nullptr;

constexpr int FPS = 60;
constexpr int DELAY_TIME = static_cast<int>(1000.0f/FPS); // Gives the amount of time we need to delay the game between loops to keep the frame rate constant. (1000 = number of milliseconds in a second)
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

	if (!TheWindow::Instance()->init("Jamie's Really Cool Game", 640, 480))
		return false;

	if (!TheRenderer::Instance()->init())
		return false;
	
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
			SDL_Delay((int)(DELAY_TIME - frameTime));
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
/// Sets the game to end at the start of next frame
/// </summary>
void Game::quit()
{
	m_bRunning = false;
}

GameStateMachine* Game::getStateMachine()
{
	return m_pGameStateMachine;
}

Game* Game::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new Game();
	}
	return s_pInstance;
}
