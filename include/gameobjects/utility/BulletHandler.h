#pragma once

class PlayerBullet;
class AlienBullet;
class Level;

/// <summary>
/// Handles all generated bullets: creation, usage and deletion
/// </summary>
class BulletHandler
{
public:
	void addPlayerBullet(int xPos, int yPos);
	void addAlienBullet(int xPos, int yPos);

	void updateBullets();
	void drawBullets();

	void clearBullets();

	void setLevel(Level* level) { m_level = level; };

	static BulletHandler* Instance() // Get instance
	{
		if (!s_pInstance)
			s_pInstance = new BulletHandler();
		return s_pInstance;
	}

private:
	static BulletHandler* s_pInstance;

	// Current PlayerBullet (only one can exist at one time)
	PlayerBullet* m_playerBullet;

	// All current AlienBullets
	std::vector<AlienBullet*> m_alienBullets;
	const int m_maxAlienBullets;

	// Current Level to give the bullets information on the other objects to collide with
	Level* m_level;

	BulletHandler() :m_playerBullet(nullptr), m_maxAlienBullets(5), m_level(nullptr) {}						// Prevent outside unwanted construction
	BulletHandler(const BulletHandler&) :m_playerBullet(nullptr), m_maxAlienBullets(5), m_level(nullptr) {}	// Prevent construction by copying
	BulletHandler& operator=(const BulletHandler&) {};									// Prevent assignment
	~BulletHandler() {};																// Prevent outside unwanted destruction
};
typedef BulletHandler TheBulletHandler;
