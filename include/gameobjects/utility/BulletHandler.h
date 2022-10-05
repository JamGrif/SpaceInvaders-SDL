#pragma once

class PlayerBullet;


class BulletHandler
{
public:
	void addPlayerBullet(int xPos, int yPos);

	void updateBullets();
	void drawBullets();

	void cleanBullets();

	// Singleton instance get
	static BulletHandler* Instance();
private:
	BulletHandler();
	static BulletHandler* s_pInstance;

	PlayerBullet* m_playerBullet; // Only one PlayerBullet can exist at one time

};
typedef BulletHandler TheBulletHandler;
