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

	virtual void loadObject(std::unique_ptr<LoaderParams> pParams);

	virtual void drawObject();
	virtual void updateObject();

private:

};

class ClickButtonCreator :
	public BaseCreator
{
	std::shared_ptr<BaseGameObject> createGameObject() const
	{
		return std::make_shared<ClickButton>();
	}
};
