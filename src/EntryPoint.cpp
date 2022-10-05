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

class MyClass
{
public:
	MyClass() {}
	~MyClass() {}
private:

};

int main(int argc, char* args[])
{

	MyClass* test = new MyClass;
	delete test;

	if (!TheGame::Instance()->gameInit())
		return 1;
	else
		TheGame::Instance()->gameLoop();

	TheGame::Instance()->gameClean();

	return 0;
}
