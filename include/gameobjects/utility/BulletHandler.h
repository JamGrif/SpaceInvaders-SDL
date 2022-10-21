#pragma once

class PlayerBullet;
class AlienBullet;
class Level;

class Block;
class Player;
class Alien;
class AlienBoss;
class BaseGameObject;

/// <summary>
/// Handles all generated bullets: creation, usage and deletion
/// </summary>
class BulletHandler
{
public:
	BulletHandler(std::vector<std::shared_ptr<Block>>& allblocks, std::vector<std::shared_ptr<Alien>>& allAliens, std::weak_ptr<Player> player, std::weak_ptr<AlienBoss> alienboss);
	~BulletHandler();

	void addPlayerBullet(int xPos, int yPos);
	void addAlienBullet(int xPos, int yPos);

	void updateBullets();
	void drawBullets();

	void clearBullets();

private:

	std::vector<std::shared_ptr<Block>>* m_allBlocks;
	std::vector<std::shared_ptr<Alien>>* m_allAliens;
	std::weak_ptr<Player> m_player;
	std::weak_ptr<AlienBoss> m_alienBoss;

	// Current PlayerBullet (only one can exist at one time)
	std::unique_ptr<PlayerBullet> m_playerBullet;

	// All current AlienBullets
	std::vector<std::unique_ptr<AlienBullet>> m_alienBullets;
	const int m_maxAlienBullets;

};
typedef BulletHandler TheBulletHandler;
