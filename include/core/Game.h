#pragma once

// Forward Declaration
class GameStateMachine;

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

	GameStateMachine* getStateMachine();

	// Singleton instance get
	static Game* Instance(); 
private:
	Game();
	static Game* s_pInstance;

	GameStateMachine* m_pGameStateMachine;

	bool m_bRunning;
};
typedef Game TheGame;
