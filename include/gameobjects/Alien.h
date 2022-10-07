#pragma once
#include "SDLGameObject.h"

class Alien :
    public SDLGameObject
{
public:
	Alien();
	~Alien();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

    virtual void drawObject();
    virtual void updateObject();

	bool checkIfReachedEdge();
	void switchDirections();

	void setDying();

	bool isDead() const { return m_bDead; }

private:

	// The aliens move as one, not independently so there movement is different than Player class
	bool m_bMoveLeft;

	float m_downAmount; // Amount the alien will move down by when it reaches an edge

	bool m_bDead;
	bool m_bDying;
	float m_timeSpentDying; // Current time spent dying
	float m_timeAloudDying; // When alien has been dying for this amount of time, change to dead

	std::string m_deadTextureID;

	

};

class AlienCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new Alien();
	}
};

