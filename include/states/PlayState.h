#pragma once
#include "states/BaseState.h"

class Player;
class Alien;
class AlienBoss;
class Block;
class BulletHandler;

/// <summary>
/// The state which has the main Space Invader game
/// </summary>
class PlayState :
    public BaseState
{
public:
	PlayState()
		:m_SelectedNextShotTime_ms(0), m_maxNextShotTime_ms(2000), m_minNextShotTime_ms(250),
		m_currentNextShotTime_ms(0), m_bFirstCheckDying(false), m_bAllowedToSpawnBullets(true)
	{}
	~PlayState() {}

	virtual bool onEnterState() override;
	virtual bool onExitState() override;

	virtual void updateState() override;
	virtual void renderState() override;

	virtual std::string getStateID() const override { return s_playID; }

private:
	static const std::string s_playID;

	std::shared_ptr<BulletHandler> m_pBulletHandler;

	static std::string s_textCallback1();

	// Player and AlienBoss exist in the gameobjects vector, this is simply a way to reference them by storing their address
	std::weak_ptr<Player>	m_player;
	std::weak_ptr<AlienBoss> m_alienBoss;

	// All Alien and Block objects are moved out of the total gameobjects vector to be in their own vectors
	std::vector<std::shared_ptr<Alien>> m_allAliens;
	std::vector<std::shared_ptr<Block>>	m_allBlocks;

	// Prep time at start of PlayState round, no action is taken until this time is taken
	int m_currentPrepTime = 0;
	int m_selectedPretTime = 2000;
	bool m_bInPrep = true;

	// Time until the next alien is chosen to shoot, chosen randomly between minNextShotTime and maxNextShotTime
	int m_SelectedNextShotTime_ms;
	int m_minNextShotTime_ms;
	int m_maxNextShotTime_ms;

	// Current time waited for next shot
	int m_currentNextShotTime_ms;

	bool m_bFirstCheckDying;
	bool m_bAllowedToSpawnBullets;
};

