#pragma once
#include "gameobjects/Button.h"

class MenuButton :
    public Button
{
public:
	MenuButton();
	~MenuButton();

	virtual void loadObject(std::unique_ptr<LoaderParams> const& pParams);

	virtual void drawObject();
	virtual void updateObject();

private:

	bool m_bPlayedSound;
};

class MenuButtonCreator :
	public BaseCreator
{
	BaseGameObject* createGameObject() const
	{
		return new MenuButton();
	}
};
