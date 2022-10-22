#pragma once
#include "gameobjects/Alien.h"

/// <summary>
/// AlienBoss objects that that appear during gameplay
/// </summary>
class AlienBoss :
    public Alien
{
public:
	AlienBoss();
	~AlienBoss();

	virtual void	loadObject(std::unique_ptr<LoaderParams> const& pParams) override;

	virtual void	drawObject() override;
	virtual void	updateObject() override;

	bool			getDead() const { return m_bDead; }

private:
	void			resetAlien();

	bool m_bDead;

	// Store alive texture ID to use when alien respawns
	std::string m_aliveTextureID;

	// The AlienBoss will respawn between this range
	const int m_minimumRespawnTime_ms;
	const int m_maximumRespawnTime_ms;

	// Selected respawn time between minimum and maximum respawn time
	int m_selectedRespawnTime_ms;

	// Current time AlienBoss has spent dying
	int m_currentRespawnTime_ms;

	// The AlienBoss will select a random score to give upon its death between a range
	const int m_minimumScoreWorth;
	const int m_maximumScoreWorth;

	// Position the AlienBoss will spawn in when it respawns
	Vector2D leftSpawnPosition;
	Vector2D rightSpawnPosition;

	bool m_bSoundPlaying;
};


class AlienBossCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<AlienBoss>();
	}
};


