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

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams) override;

    virtual void	drawObject() override;
    virtual void	updateObject() override;

	void			respawnPlayer();

	void			setBulletHandler(std::weak_ptr<BulletHandler> bh) { m_stateBulletHandler = bh; }

	void			setDying();

	bool			getDead() const { return m_bDead; }
	bool			getDying() const { return m_bDying; }

private:

	std::weak_ptr<BulletHandler> m_stateBulletHandler;

	bool			m_bDead;
	bool			m_bDying;

	// When player has been dying for this amount of time, set to dead
	// Current time spent dying
	const uint16_t	m_selectedDyingTime_ms;
	uint16_t		m_currentDyingTime_ms;

	Vector2D		m_respawnPosition;

	// Provides a cool down before the player can next shoot - prevents rapid fire into blocks
	bool			m_bReadyToShoot;
	const uint16_t	m_selectedShotWaitTime_ms;
	uint16_t		m_currentShotWaitTime_ms;
};

class PlayerCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<Player>();
	}
};

