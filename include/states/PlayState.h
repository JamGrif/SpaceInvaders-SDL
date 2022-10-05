#pragma once
#include "BaseState.h"

//class GameObject;
class SDLGameObject;
//class Level;

class Alien;

class PlayState :
    public BaseState
{
public:
	virtual bool onEnterState() override;
	virtual bool onExitState() override;

	virtual void updateState() override;
	virtual void renderState() override;

	virtual std::string getStateID() const override { return s_playID; }

private:
	static const std::string s_playID;

	std::vector<Alien*>* m_allAliens;

	int m_totalAliens;
	int m_currentAliensDead;

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
};

