#pragma once

// Forward Declaration
class GameStateMachine;

enum class EndingOutcome
{
	Win_KilledAllAliens = 0,
	Lose_NoLives = 1,
	Lose_AliensReachedEnd = 2
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


};
typedef Game TheGame;
