#pragma once

class GameStateMachine;

enum class GameStateOutcome
{
	None					= 0,
	Win_KilledAllAliens		= 1,
	Lose_NoLives			= 2,
	Lose_AliensReachedEnd	= 3
};

/// <summary>
/// Encapsulates the entire program, providing functions to start it
/// </summary>
class Game
{
public:
	// Called from EntryPoint.cpp
	bool			gameInit();
	void			gameLoop();
	void			gameClean();

	// Called from gameLoop()
	void			renderGame();
	void			updateGame();
	void			handleEventsGame();

	void			quitGame();

	GameStateMachine* getStateMachine() const { return m_pGameStateMachine; }

	void			setGameOutcome(GameStateOutcome e);
	std::string		getGameOutcome() { return m_outcomeText; }

	// Player's score
	void			increaseCurrentScore(int value) { m_currentScore += value; }
	void			resetCurrentScore() { m_currentScore = 0; }
	int				getCurrentScore() const { return m_currentScore; }

	// Player's lives
	void			increaseCurrentLives();
	void			decreaseCurrentLives();
	void			resetCurrentLives() { m_currentLives = m_maxLives; }
	int				getCurrentLives() const { return m_currentLives; }

		
	static Game*	Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new Game();
		return s_pInstance;
	}

private:
	static Game*	s_pInstance;

	GameStateMachine* m_pGameStateMachine;

	// Condition for main game loop
	bool			m_bRunning;

	// Result of playing the game - Set by PlayState and used in GameOverState
	std::string		m_outcomeText;

	// Player score - in Game class to persist through different states
	int				m_currentScore;

	// Player lives - in Game class to persist through different states
	const int		m_maxLives;
	int				m_currentLives;

	Game();																// Prevent outside unwanted construction
	Game(const Game&)													// Prevent construction by copying
		:m_pGameStateMachine(nullptr), m_bRunning(false),
		m_currentScore(0), m_maxLives(3), m_currentLives(m_maxLives) {}		
	Game& operator=(const Game&) {}										// Prevent assignment
	~Game() {}															// Prevent outside unwanted destruction
};
typedef Game TheGame;
