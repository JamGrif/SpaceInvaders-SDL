#pragma once

class GameStateMachine;

enum class GameStateOutcome
{
	None					= 0,
	Win_KilledAllAliens		= 1,
	Lose_NoLives			= 2,
	Lose_AliensReachedEnd	= 3
};

class Game
{
public:

	// Called from EntryPoint.cpp
	bool gameInit();
	void gameLoop();
	void gameClean();

	// Called from gameLoop()
	void renderGame();
	void updateGame();
	void handleEventsGame();

	void quitGame();

	GameStateMachine* getStateMachine() const { return m_pGameStateMachine; }

	void setGameOutcome(GameStateOutcome e);
	std::string getGameOutcome() { return m_outcomeText; }

	void increaseCurrentScore(int value) { m_currentScore += value; }
	void resetCurrentScore() { m_currentScore = 0; }
	int getCurrentScore() const { return m_currentScore; }

	void increaseCurrentLives();
	void decreaseCurrentLives();
	void resetCurrentLives() { m_currentLives = m_maxLives; }
	int getCurrentLives() const { return m_currentLives; }


	static Game* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new Game();
		return s_pInstance;
	}

private:
	Game();
	static Game* s_pInstance;

	GameStateMachine* m_pGameStateMachine;

	bool m_bRunning;

	// Result of playing the game - Set by PlayState and used in GameOverState
	GameStateOutcome m_outcome;
	std::string m_outcomeText;

	// Player score - in Game class to persist through different states
	int m_currentScore;

	// Player lives - in Game class to persist through different states
	const int m_maxLives;
	int m_currentLives;
};
typedef Game TheGame;
