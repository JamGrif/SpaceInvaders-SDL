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

/// <summary>
/// Update all layers used in this level
/// </summary>
void Level::updateLevel()
{
	for (auto layer : m_layers)
	{
		layer->updateLayer();
	}
}

/// <summary>
/// Draw all layers used in this level
/// </summary>
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
