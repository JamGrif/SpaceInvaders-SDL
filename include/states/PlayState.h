#pragma once
#include "BaseState.h"

class Player;
class Alien;
class AlienBoss;

class PlayState :
    public BaseState
{
public:
	PlayState();
	~PlayState(); 

	virtual bool onEnterState() override;
	virtual bool onExitState() override;

	virtual void updateState() override;
	virtual void renderState() override;

	virtual std::string getStateID() const override { return s_playID; }

private:
	static const std::string s_playID;

	static std::string s_textCallback1();

	Player*	m_player;
	std::vector<Alien*>* m_allAliens;
	AlienBoss* m_alienBoss;

	int m_totalAliens;
	int m_currentAliensDead;

	// Time until the next alien is chosen to shoot
	int m_minNextShotTime_ms;
	int m_maxNextShotTime_ms;
	int m_SelectedNextShotTime_ms;

	int m_currentNextShotTime_ms;

	bool m_bFirstCheckDying = false;
	bool m_bAllowedToSpawnBullets = true;
};

