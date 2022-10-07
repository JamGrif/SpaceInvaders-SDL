#pragma once

class PlayerBullet;
class AlienBullet;
class Level;

class BulletHandler
{
public:
	void addPlayerBullet(int xPos, int yPos);
	void addAlienBullet(int xPos, int yPos);

	void updateBullets();
	void drawBullets();

	void clearBullets();

	void setLevel(Level* level) { m_level = level; };

	static BulletHandler* Instance() // Instance get
	{
		if (!s_pInstance)
			s_pInstance = new BulletHandler();
		return s_pInstance;
	}

private:
	BulletHandler();
	static BulletHandler* s_pInstance;

	PlayerBullet* m_playerBullet; // Only one PlayerBullet can exist at one time
	std::vector<AlienBullet*> m_alienBullets;

	const int m_maxAlienBullets = 5;

	Level* m_level;

};
typedef BulletHandler TheBulletHandler;
