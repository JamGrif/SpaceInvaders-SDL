/*
	.h
	#pragma once
	#parent class header include
	#
	#C++ libraries include 
	#
	#dependencies libraries include 
	#
	#other this app files include
	#	core -> gameobjects -> level -> states -> misc
	#
	# forward declaration
	#
	# #defines

	.cpp
	#pch.h
	#parent class include
	#
	#C++ libraries include
	#
	#dependencies libraries include
	#
	#other this app files include
	#	core -> gameobjects -> level -> states -> misc
	#
	# #defines
	#
	# static variable definitions
*/

#include "pch.h"
#include "core/Game.h"

#include "SDL2/SDL.h" // SDL version of main()

// Enable console if debug mode
#ifdef _DEBUG
	#include <windows.h>
	#define startConsole AllocConsole(); freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#else
	#define startConsole
#endif

int main(int argc, char* args[])
{
	startConsole;

	if (!TheGame::Instance()->gameInit())
		return 1;
	else
		TheGame::Instance()->gameLoop();

	TheGame::Instance()->gameClean();

	return 0;
}
