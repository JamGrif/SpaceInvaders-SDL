#include "pch.h"
#include "gameobjects/GameObjectFactory.h"

//GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;
GameObjectFactory* GameObjectFactory::s_pInstance = 0;

GameObjectFactory* GameObjectFactory::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new GameObjectFactory();
	}
	return s_pInstance;
}
