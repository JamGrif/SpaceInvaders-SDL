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
		:m_currentPrepTime_ms(0), m_selectedPrepTime_ms(1500), m_bInPrep(true),
		m_selectedNextShotTime_ms(0), m_maxNextShotTime_ms(2000), m_minNextShotTime_ms(250),
		m_currentNextShotTime_ms(0), m_bFirstCheckDying(false), m_bAllowedToSpawnBullets(true)
	{}
	~PlayState() {}

	virtual bool				onEnterState() override;
	virtual bool				onExitState() override;

	virtual void				updateState() override;
	virtual void				renderState() override;

	virtual std::string			getStateID() const override { return s_playID; }

private:
	static const std::string	s_playID;

	std::shared_ptr<BulletHandler> m_pBulletHandler;

	static std::string			s_textCallback1();

	// Player and AlienBoss exist in the gameobjects vector, this is simply a way to reference them by storing their address
	std::weak_ptr<Player>		m_pPlayer;
	std::weak_ptr<AlienBoss>	m_pAlienBoss;

	// All Alien and Block objects are moved out of the total gameobjects vector to be in their own vectors
	std::vector<std::shared_ptr<Alien>> m_allAliens;
	std::vector<std::shared_ptr<Block>>	m_allBlocks;

	// Prep time at start of PlayState round, no action is taken until this time is taken
	uint16_t					m_currentPrepTime_ms;
	uint16_t					m_selectedPrepTime_ms;
	bool						m_bInPrep;

	// Time until the next alien is chosen to shoot, chosen randomly between minNextShotTime and maxNextShotTime
	uint16_t					m_selectedNextShotTime_ms;
	uint16_t					m_minNextShotTime_ms;
	uint16_t					m_maxNextShotTime_ms;

	// Current time waited for next shot
	uint16_t					m_currentNextShotTime_ms;

	// This ensures the bullets are only cleared once when player first dies
	bool						m_bFirstCheckDying;

	bool						m_bAllowedToSpawnBullets;
};

