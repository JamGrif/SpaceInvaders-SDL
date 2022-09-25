#pragma once

#include "GameObject.h"

/// <summary>
/// Base class for the game state Finite State Machine
/// </summary>
class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;
};

