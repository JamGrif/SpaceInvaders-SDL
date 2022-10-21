#pragma once
#include "gameobjects/SDLGameObject.h"

class BulletHandler;

/// <summary>
/// Player object that appear during gameplay, controlled by the user
/// </summary>
class Player :
    public SDLGameObject
{
public:
    Player();
    ~Player();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

    virtual void drawObject();
    virtual void updateObject();

	void respawnPlayer();

	void setBulletHandler(std::weak_ptr<BulletHandler> bh) { m_stateBulletHandler = bh; }

	void setDying();

	bool getDead() const { return m_bDead; }
	bool getDying() const { return m_bDying; }

private:

	std::weak_ptr<BulletHandler> m_stateBulletHandler;

	bool m_bDead;
	bool m_bDying;

	// Current time spent dying
	int m_timeSpentDying_ms;

	// When player has been dying for this amount of time, set to dead
	const int m_timeAloudDying_ms;

	Vector2D m_respawnPosition;
};

class PlayerCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<Player>();
	}
};

