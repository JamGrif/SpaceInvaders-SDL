#pragma once
#include "gameobjects/SDLGameObject.h"

enum class MovingDirection
{
	None = 0,
	Left = 1,
	Right = 2
};

/// <summary>
/// Alien objects that appear during gameplay
/// </summary>
class Alien :
    public SDLGameObject
{
public:
	Alien();
	~Alien();

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams) override;

    virtual void	drawObject() override;
    virtual void	updateObject() override;

	void			setDying();
	
	bool			checkIfReachedEdge() const;
	void			switchDirection();

protected:

	// Amount the alien will move down by when it reaches an edge
	float m_downAmount; 

	bool m_bDying;

	MovingDirection m_direction;

	// Current time spent dying
	uint16_t m_timeSpentDying_ms;

	// When alien has been dying for this amount of time, set to dead
	uint16_t m_timeAloudDying_ms;

	// Sprite the Alien will use upon death
	std::string m_deadTextureID;

	// Score to give upon alien death
	uint16_t m_selectedScoreWorth;
};

class AlienCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<Alien>();
	}
};

