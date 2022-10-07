#pragma once
#include "SDLGameObject.h"

class Player :
    public SDLGameObject
{
public:
    Player();
    ~Player();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

    virtual void drawObject();
    virtual void updateObject();

	void respawn();

	void setDying();

	bool getDead() const { return m_bDead; }
	bool getDying() const { return m_bDying; }

	int getPlayerLives() const { return m_playerCurrentLives; }

private:

	bool m_bDead;
	bool m_bDying;

	float m_timeSpentDying = 0;
	float m_timeMaxDying = 2000;

	Vector2D m_respawnPosition;

	int m_playerMaxLives;
	int m_playerCurrentLives;

};

class PlayerCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new Player();
	}
};

