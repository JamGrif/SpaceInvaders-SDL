#include "pch.h"
#include "Level.h"

#include "Layer.h"

Level::~Level()
{

}

void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
}

void Level::render()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}

std::vector<Tileset>* Level::getTilesets()
{
	return &m_tilesets;
}

std::vector<Layer*>* Level::getLayers()
{
	return &m_layers;
}

Level::Level()
{

}
