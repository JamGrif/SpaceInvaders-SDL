#include "pch.h"
#include "core/Game.h"

#include "core/Window.h"
#include "core/Renderer.h"
#include "core/InputHandler.h"
#include "core/SoundManager.h"
#include "core/TextManager.h"
#include "gameobjects/utility/GameObjectFactory.h"
#include "states/MainMenuState.h" 
#include "states/utility/GameStateMachine.h"

#define INITIALIZE_SUCCESS 0

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 704

Game* Game::s_pInstance = nullptr;



/// <summary>
/// Sets up systems used by the game, required before the game loop can start
/// </summary>
bool Game::gameInit()
{
	// Generate new seed
	srand(static_cast<unsigned int>(time(0)));

	// Initialize all SDL subsystems and program objects
	if (SDL_Init(SDL_INIT_EVERYTHING) != INITIALIZE_SUCCESS)
	{
		std::cout << "SDL could not initialize" << std::endl;
		return false;
	}

	if (!TheWindow::Instance()->init("SpaceInvaders-SDL", WINDOW_WIDTH, WINDOW_HEIGHT))
		return false;

	if (!TheRenderer::Instance()->init())
		return false;

	if (!TheInputHandler::Instance()->init())
		return false;

	if (!TheSoundManager::Instance()->init())
		return false;

	if (!TheTextManager::Instance()->init())
		return false;
	
	if (!TheGameObjectFactory::Instance()->init())
		return false;

	// Create the game state machine and set default state
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->setStateUpdate(StateMachineAction::changeToMain);

	setGameOutcome(GameStateOutcome::None);

	TheSoundManager::Instance()->playMusic("music");

	m_bRunning = true;
	return true;
}

/// <summary>
/// The entire program loop, must run gameInit() first
/// </summary>
void Game::gameLoop()
{
	// Begin the program clock
	TheProgramClock::Instance()->init();

	while (m_bRunning)
	{
		TheProgramClock::Instance()->tick();

		handleEventsGame();
		updateGame();
		renderGame();
	}
}

/// <summary>
/// Cleans and deletes all systems of SDL and the program
/// </summary>
void Game::gameClean()
{
	// Clean in the reverse order of creation
	std::cout << "before delete gamestatemachine" << std::endl;
	delete m_pGameStateMachine;
	std::cout << "after delete gamestatemachine" << std::endl;

	TheGameObjectFactory::Instance()->clean();
	TheTextManager::Instance()->clean();
	TheSoundManager::Instance()->clean();
	TheInputHandler::Instance()->clean();
	TheRenderer::Instance()->clean();
	TheWindow::Instance()->clean();
	SDL_Quit();
}

/// <summary>
/// Render the current state in the game state machine
/// </summary>
void Game::renderGame()
{
	TheRenderer::Instance()->startOfFrame();

	m_pGameStateMachine->renderCurrentState();

	TheRenderer::Instance()->EndOfFrame();
}

/// <summary>
/// Update the current state in the game state machine
/// </summary>
void Game::updateGame()
{
	m_pGameStateMachine->updateCurrentState();
}

/// <summary>
/// Checks the input handler for input updates
/// </summary>
void Game::handleEventsGame()
{
	TheInputHandler::Instance()->update();

	// Check if the current state is set to change
	if (m_pGameStateMachine->checkForStateChange())
	{
		m_pGameStateMachine->changeCurrentState();
	}
}

/// <summary>
/// Sets the game to end at the start of next frame
/// </summary>
void Game::quitGame()
{
	m_bRunning = false;
}

/// <summary>
/// Set and store the outcome of the game.
/// Called from PlayState and read from GameOverState
/// </summary>
void Game::setGameOutcome(GameStateOutcome e)
{
	switch (e)
	{
		case GameStateOutcome::None:
			m_outcomeText = "u shouldn't be here";
			break;

		case GameStateOutcome::Win_KilledAllAliens:
			m_outcomeText = "Killed all aliens";
			break;

		case GameStateOutcome::Lose_NoLives:
			m_outcomeText = "Lost all your lives";
			break;

		case GameStateOutcome::Lose_AliensReachedEnd:
			m_outcomeText = "Aliens reached end";
			break;
	}
}

/// <summary>
/// Increment the current lives, limiting it to maxLives
/// </summary>
void Game::increaseCurrentLives()
{
	m_currentLives++;
	if (m_currentLives > m_maxLives)
		m_currentLives = m_maxLives;
}

/// <summary>
/// Decrement the current lives, limiting it to 0
/// </summary>
void Game::decreaseCurrentLives()
{
	m_currentLives--;
	if (m_currentLives < 0)
		m_currentLives = 0;
}

Game::Game()
	:m_pGameStateMachine(nullptr), m_bRunning(false), m_currentScore(0), m_maxLives(3), m_currentLives(m_maxLives)
{
}
