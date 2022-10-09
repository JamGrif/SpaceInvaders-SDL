#pragma once
#include "SDLGameObject.h"

enum class MovingDirection
{
	None = 0,
	Left = 1,
	Right = 2
};

class AlienBoss :
    public SDLGameObject
{
public:
	AlienBoss();
	~AlienBoss();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

	void reset();

	void setDying();
	void setDead();


private:

	// Alien is currently moving through the level, allowing the player to shoot it
	bool m_bActive;

	std::string m_aliveTextureID;
	std::string m_deadTextureID = "alienBossDead";

	//bool m_bDead;
	bool m_bDying = false;
	int m_timeSpentDying = 0;; // Current time spent dying
	int m_timeAloudDying = 200; // When alien has been dying for this amount of time, change to dead

	// The AlienBoss will repsawn between this range and its chosen respawn time is stored in m_selectedRespawnTime_ms;
	const int m_minimumRespawnTime_ms;
	const int m_maximumRespawnTime_ms;
	int m_selectedRespawnTime_ms;

	int m_currentRespawnTime_ms;

	// The AlienBoss will select a random score to give upon its death between a range
	const int m_minimumScoreWorth;
	const int m_maximumScoreWorth;
	int m_selectedScoreWorth;

	MovingDirection m_direction = MovingDirection::None;

	Vector2D leftSpawnPosition{-100, 100};
	Vector2D rightSpawnPosition{800, 100};
};


class AlienBossCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new AlienBoss();
	}
};


