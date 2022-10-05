#include "pch.h"
#include "core/Game.h"

#include "core/Window.h"
#include "core/Renderer.h"
#include "core/InputHandler.h"
#include "gameobjects/MenuButton.h"
#include "gameobjects/Alien.h"
#include "gameobjects/Player.h"
#include "gameobjects/utility/GameObjectFactory.h"
#include "gameobjects/Bullet.h"
#include "states/MainMenuState.h" 
#include "states/utility/GameStateMachine.h"

Game* Game::s_pInstance = nullptr;

constexpr int FPS = 60;
constexpr int DELAY_TIME = static_cast<int>(1000.0f/FPS); // Gives the amount of time we need to delay the game between loops to keep the frame rate constant. (1000 = number of milliseconds in a second)
Uint32 frameStart, frameTime;


/// <summary>
/// Initializes all SDL and program systems
/// </summary>
bool Game::gameInit()
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

	TheProgramClock::Instance()->init();

	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Alien", new AlienCreator());
	TheGameObjectFactory::Instance()->registerType("SDLGameObject", new SDLGameObjectCreator());
	TheGameObjectFactory::Instance()->registerType("PlayerBullet", new PlayerBulletCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->pushState(new MainMenuState());

	m_bRunning = true;
	return true;
}

/// <summary>
/// The entire program loop
/// </summary>
void Game::gameLoop()
{
	// SDL_GetTicks() returns the amount of milliseconds since SDL_Init was called
	while (m_bRunning)
	{
		TheProgramClock::Instance()->tick();
		frameStart = SDL_GetTicks();

		handleEventsGame();
		updateGame();
		renderGame();

		frameTime = SDL_GetTicks() - frameStart; // Stores how long it took for frame to run

		if (frameTime < DELAY_TIME) // If it is less than the time we want a frame to take, we call SDL_Delay to make the loop wait for the amount of time we want, subtracting how long the loop already took to complete
			SDL_Delay((int)(DELAY_TIME - frameTime));
	}
}

/// <summary>
/// Cleans and deletes all systems of SDL and the program
/// </summary>
void Game::gameClean()
{
	delete m_pGameStateMachine;
	TheInputHandler::Instance()->clean();
	TheRenderer::Instance()->clean();
	TheWindow::Instance()->clean();
	SDL_Quit();
}

/// <summary>
/// Performs all drawing operations of the program
/// </summary>
void Game::renderGame()
{
	TheRenderer::Instance()->startOfFrame();

	m_pGameStateMachine->renderCurrentState();

	TheRenderer::Instance()->EndOfFrame();
}

/// <summary>
/// Updates all objects of the program
/// </summary>
void Game::updateGame()
{
	m_pGameStateMachine->updateCurrentState();
}

/// <summary>
/// Checks the mouse and keyboard for input
/// </summary>
void Game::handleEventsGame()
{
	TheInputHandler::Instance()->update();

	if (m_pGameStateMachine->IsActionToChange())
	{
		m_pGameStateMachine->doAChange();
	}
}

/// <summary>
/// Sets the game to end at the start of next frame
/// </summary>
void Game::quitGame()
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

Game::Game()
	:m_pGameStateMachine(nullptr), m_bRunning(false)
{
}
