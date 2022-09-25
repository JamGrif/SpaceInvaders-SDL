#pragma once

//#include "SDL.h"
//#include "TextureManager.h"
//#include "Player.h"
//#include "Enemy.h"

//#include "SDLRenderer.h"

// Forward Declaration
class GameStateMachine;
class GameObject;

class Game
{
public:

	bool init();
	void loop();

	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();

	bool getRunning();
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	static Game* Instance(); // Singleton
private:
	Game();
	static Game* s_pInstance;

	std::vector<GameObject*> m_gameObjects;

	GameStateMachine* m_pGameStateMachine;

	bool m_bRunning;
};
typedef Game TheGame;
