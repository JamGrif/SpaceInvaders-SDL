#include "pch.h"
#include "level/Level.h"

#include "level/BaseLayer.h"

Level::~Level()
{
	for (auto layer : m_layers)
	{
		delete layer;
	}
}

void Level::updateLevel()
{
	for (auto layer : m_layers)
	{
		layer->updateLayer();
	}
}

void Level::renderLevel()
{
	for (auto layer : m_layers)
	{
		layer->renderLayer();
	}
}



Level::Level()
{
}
