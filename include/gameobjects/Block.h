#pragma once
#include "gameobjects/SDLGameObject.h"

enum class BlockHealth
{
	Full = 0,
	SlightDamage = 1,
	MinorDamage = 2,
	MajorDamage = 3,
	Gone = 4
};

/// <summary>
/// Blocks that appear during gameplay
/// </summary>
class Block :
    public SDLGameObject
{
public:
	Block();
	~Block();

	virtual void	loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void	drawObject();
	virtual void	updateObject();

	//bool			isDestroyed() { return m_bDestoryed; }

	void			hit();

private:

	//bool m_bDestoryed;

	int m_blockHealth;
};

class BlockCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<Block>();
	}
};


