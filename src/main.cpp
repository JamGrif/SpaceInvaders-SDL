#include "Game.h"

#include <SDL.h>

// test

int main(int argc, char* args[])
{
	if (!TheGame::Instance()->init())
		return 1;
	else
		TheGame::Instance()->loop();

	TheGame::Instance()->clean();

	return 0;
}
