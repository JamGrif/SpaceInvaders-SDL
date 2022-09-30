#pragma once

// Forward Declaration
class GameStateMachine;

class Game
{
public:
	bool init();
	void loop();
	void clean();

	void render();
	void update();
	void handleEvents();

	void quit();

	GameStateMachine* getStateMachine();

	static Game* Instance(); // Singleton
private:
	Game();
	static Game* s_pInstance;

	GameStateMachine* m_pGameStateMachine;

	bool m_bRunning;
};
typedef Game TheGame;
