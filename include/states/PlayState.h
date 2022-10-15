#pragma once
#include "states/BaseState.h"

class Player;
class Alien;
class AlienBoss;
class Block;

/// <summary>
/// The state which has the main Space Invader game
/// </summary>
class PlayState :
    public BaseState
{
public:
	PlayState()
		:m_player(nullptr), m_alienBoss(nullptr), m_allAliens(nullptr), m_allBlocks(nullptr),
		m_SelectedNextShotTime_ms(0), m_maxNextShotTime_ms(2000), m_minNextShotTime_ms(250),
		m_currentNextShotTime_ms(0), m_bFirstCheckDying(false), m_bAllowedToSpawnBullets(true)
	{
	}

	virtual bool onEnterState() override;
	virtual bool onExitState() override;

	virtual void updateState() override;
	virtual void renderState() override;

	virtual std::string getStateID() const override { return s_playID; }

private:
	static const std::string s_playID;

	static std::string s_textCallback1();

	Player*	m_player;
	AlienBoss* m_alienBoss;
	std::vector<Alien*>* m_allAliens;
	std::vector<Block*>* m_allBlocks;

	// Time until the next alien is chosen to shoot, chosen randomly between minNextShotTime and maxNextShotTime
	int m_SelectedNextShotTime_ms;
	int m_minNextShotTime_ms;
	int m_maxNextShotTime_ms;

	// Current time waited for next shot
	int m_currentNextShotTime_ms;

	bool m_bFirstCheckDying;
	bool m_bAllowedToSpawnBullets;
};

