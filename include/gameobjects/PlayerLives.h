#pragma once
#include "gameobjects/SDLGameObject.h"

/// <summary>
/// Represents the player lives icon during gameplay
/// Only gets drawn if current lives is higher than m_livesRequired
/// </summary>
class PlayerLives :
    public SDLGameObject
{
public:
	PlayerLives();
	~PlayerLives();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

private:

	// Minimum lives required for the player lives icon to get drawn
	int m_livesRequired;

	bool m_bDraw;
};

class PlayerLivesCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new PlayerLives();
	}
};
