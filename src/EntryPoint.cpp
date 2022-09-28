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
	#	core -> gameobjects -> states -> misc
	#
	# forward declaration

	.cpp
	#pch.h
	#parent class include
	#
	#C++ libraries include
	#
	#dependencies libraries include
	#
	#other this app files include
	#	core -> gameobjects -> states -> misc
	#
	# static variable definitions


*/

#include "pch.h"

#include "core/Game.h"

int main(int argc, char* args[])
{
	if (!TheGame::Instance()->init())
		return 1;
	else
		TheGame::Instance()->loop();

	TheGame::Instance()->clean();

	return 0;
}
