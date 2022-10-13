#pragma once
#include "gameobjects/Button.h"

/// <summary>
/// Click style button that calls a specific button when clicked on
/// </summary>
class ClickButton :
    public Button
{
public:
	ClickButton();
	~ClickButton();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

private:

};

class ClickButtonCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new ClickButton();
	}
};
