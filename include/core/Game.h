#pragma once

class GameStateMachine;

enum class GameStateOutcome
{
	None					= 0,
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

	void			setGameOutcome(GameStateOutcome e);
	std::string		getGameOutcome() { return m_outcomeText; }

	// Player's score
	void			increaseCurrentScore(int value) { m_currentScore += value; }
	void			resetCurrentScore() { m_currentScore = 0; }
	uint16_t		getCurrentScore() const { return m_currentScore; }

	// Player's lives
	void			increaseCurrentLives();
	void			decreaseCurrentLives();
	void			resetCurrentLives() { m_currentLives = m_maxLives; }
	int8_t			getCurrentLives() const { return m_currentLives; }

	GameStateMachine* getStateMachine() const { return m_pGameStateMachine; }
		
	static Game*	Instance() // Get instance
	{
		static Game* s_pInstance = new Game;
		return s_pInstance;
	}

private:

	GameStateMachine* m_pGameStateMachine;

	// Condition for main game loop
	bool			m_bRunning;

	// Result of playing the game - Set by PlayState and used in GameOverState
	std::string		m_outcomeText;

	// Player score - in Game class to persist through different states
	uint16_t		m_currentScore;

	// Player lives - in Game class to persist through different states
	const uint8_t	m_maxLives;
	int8_t			m_currentLives;

	Game();									// Prevent outside unwanted construction
	Game(const Game&) = delete;				// Prevent construction by copying
	Game& operator=(const Game&) = delete;	// Prevent assignment
	~Game() {}								// Prevent outside unwanted destruction
};
typedef Game TheGame;
