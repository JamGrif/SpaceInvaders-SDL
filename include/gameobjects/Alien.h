#pragma once
#include "SDLGameObject.h"

enum class MovingDirection
{
	None = 0,
	Left = 1,
	Right = 2
};

class Alien :
    public SDLGameObject
{
public:
	Alien();
	~Alien();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams) override;

    virtual void drawObject() override;
    virtual void updateObject() override;

	void setDying();

	bool checkIfReachedEdge();
	void switchDirection();

	bool isDead() const { return m_bDead; }

protected:

	float m_downAmount; // Amount the alien will move down by when it reaches an edge

	bool m_bDead;
	bool m_bDying;

	MovingDirection m_direction;

	int m_timeSpentDying_ms; // Current time spent dying
	int m_timeAloudDying_ms;  // When alien has been dying for this amount of time, change to dead

	std::string m_deadTextureID;

	// Score to give upon alien death
	int m_selectedScoreWorth;
};

class AlienCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new Alien();
	}
};

