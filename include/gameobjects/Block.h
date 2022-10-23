#pragma once
#include "gameobjects/SDLGameObject.h"

enum class BlockHealth;

/// <summary>
/// Blocks that appear during gameplay
/// </summary>
class Block :
    public SDLGameObject
{
public:
	Block();
	~Block();

	virtual void	loadObject(std::unique_ptr<LoaderParams> pParams);

	virtual void	drawObject();
	virtual void	updateObject();

	void			hitObject();

private:

	BlockHealth m_blockHealth;
};

class BlockCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<Block>();
	}
};


