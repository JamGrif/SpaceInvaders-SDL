#include "pch.h"
#include "core/Game.h"

#include "core/Window.h"
#include "core/Renderer.h"
#include "core/InputHandler.h"
#include "core/SoundManager.h"
#include "states/MainMenuState.h" 
#include "states/utility/GameStateMachine.h"
#include "gameobjects/utility/GameObjectFactory.h"
#include "gameobjects/MenuButton.h"
#include "gameobjects/Alien.h"
#include "gameobjects/Player.h"
#include "gameobjects/TextObject.h"
#include "gameobjects/PlayerLives.h"
#include "gameobjects/CheckboxButton.h"
#include "gameobjects/AlienBoss.h"

#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

#include <ctime>
#include <cstdlib>

Game* Game::s_pInstance = nullptr;

constexpr int FPS = 60;
constexpr int DELAY_TIME = static_cast<int>(1000.0f/FPS); // Gives the amount of time we need to delay the game between loops to keep the frame rate constant. (1000 = number of milliseconds in a second)
Uint32 frameStart, frameTime;

#define INITIALIZE_SUCCESS 0

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 704


/// <summary>
/// Initializes all SDL and program systems
/// </summary>
bool Game::gameInit()
{
	srand(static_cast<unsigned int>(time(0)));

	// Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != INITIALIZE_SUCCESS)
	{
		std::cout << "SDL could not initialize" << std::endl;
		return false;
	}

	if (TTF_Init() != INITIALIZE_SUCCESS)
	{
		std::cout << "TTF could not initialize" << std::endl;
		return false;
	}

	if (!TheWindow::Instance()->init("SpaceInvaders-SDL", WINDOW_WIDTH, WINDOW_HEIGHT))
		return false;

	if (!TheRenderer::Instance()->init())
		return false;
	
	TheInputHandler::Instance()->init();

	TheSoundManager::Instance()->init();

	TheSoundManager::Instance()->loadSound("res/audio/playerShoot.wav", "playerShoot");
	TheSoundManager::Instance()->loadSound("res/audio/playerExplosion.wav", "playerExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/alienExplosion.wav", "alienExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/menuMouseOver.wav", "menuMouseOver");
	TheSoundManager::Instance()->loadMusic("res/audio/music.ogg", "music");
	 
	TheSoundManager::Instance()->playMusic("music");
	
	// Register types for the LevelParser (only ones that appear in .tmx files)
	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("Alien", new AlienCreator());
	TheGameObjectFactory::Instance()->registerType("SDLGameObject", new SDLGameObjectCreator());
	TheGameObjectFactory::Instance()->registerType("PlayerLives", new PlayerLivesCreator());
	TheGameObjectFactory::Instance()->registerType("TextObject", new TextObjectCreator());
	TheGameObjectFactory::Instance()->registerType("CheckboxButton", new CheckboxButtonCreator());
	TheGameObjectFactory::Instance()->registerType("AlienBoss", new AlienBossCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->setStateUpdate(StateMachineAction::changeToMain);

	setGameOutcome(GameStateOutcome::None);

	m_bRunning = true;
	return true;
}

/// <summary>
/// The entire program loop
/// </summary>
void Game::gameLoop()
{
	TheProgramClock::Instance()->init();

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
	TheSoundManager::Instance()->clean();
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
	//std::cout << m_currentScore << std::endl;
	m_pGameStateMachine->updateCurrentState();
}

/// <summary>
/// Checks the mouse and keyboard for input
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


void Game::setGameOutcome(GameStateOutcome e)
{
	m_outcome = e;
	switch (m_outcome)
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

void Game::increaseCurrentLives()
{
	m_currentLives++;
	if (m_currentLives > m_maxLives)
		m_currentLives = m_maxLives;
}

void Game::decreaseCurrentLives()
{
	m_currentLives--;
	if (m_currentLives < 0)
		m_currentLives = 0;
}

Game::Game()
	:m_pGameStateMachine(nullptr), m_bRunning(false), m_outcome(GameStateOutcome::None), m_currentScore(0), m_maxLives(3), m_currentLives(m_maxLives)
{
}
