#pragma once
#include "SDLGameObject.h"

class Player;

class PlayerLives :
    public SDLGameObject
{
public:
	PlayerLives();
	~PlayerLives();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

	void setPlayer(Player* player) { m_pPlayer = player; }

private:

	int m_livesRequired;

	bool m_bDraw;

	Player* m_pPlayer;
};

class PlayerLivesCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new PlayerLives();
	}
};
