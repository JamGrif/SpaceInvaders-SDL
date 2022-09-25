#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include <string>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "GameStateMachine.h"

//#include "SDLRenderer.h"

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
