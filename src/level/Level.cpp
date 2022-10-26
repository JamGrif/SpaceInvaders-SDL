#include "pch.h"
#include "level/Level.h"

#include "level/TileLayer.h"

Level::~Level()
{
}

/// <summary>
/// Update all layers used in this level
/// </summary>
void Level::updateLevel()
{
	m_pTileLayer->updateLayer();
}

/// <summary>
/// Draw all layers used in this level
/// </summary>
void Level::renderLevel()
{
	m_pTileLayer->renderLayer();
}

void Level::addTileLayer(std::unique_ptr<TileLayer> layer)
{
	m_pTileLayer = std::move(layer);
}

Level::Level()
{
}
