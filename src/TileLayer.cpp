#include "pch.h"
#include "TileLayer.h"

#include "core/Window.h"
#include "Level.h"
#include "core/TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets)
	:m_position(0,0), m_velocity(0,0), m_tilesets(tilesets), m_tileSize(tileSize)
{
	// Number of columns and rows to fill the size of the game
	m_numColumns = (TheWindow::Instance()->getWindowWidth() / m_tileSize);
	m_numRows = (TheWindow::Instance()->getWindowHeight() / m_tileSize);
}

void TileLayer::update()
{
	// Uses velocity to set the maps position
	m_position += m_velocity;
	//m_velocity.setX(1);
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;

	x = m_position.getX() / m_tileSize;
	y = m_position.getY() / m_tileSize;

	x2 = static_cast<int>(m_position.getX()) % m_tileSize;
	y2 = static_cast<int>(m_position.getY()) % m_tileSize;

	// Loop through the number of columns and number of rows
	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			// Get current tile ID from the array
			int id = m_tileIDs[i + y][j + x];

			if (id == 0)
				continue;

			// Grab the correct tileset
			Tileset tileset = getTilesetByID(id);

			// Now to draw the tiles
			id--; // Decrement the ID so can draw the correct tile from the tilesheet (even if it is a position 0,0)

			// Use the drawTile function to copy across the correct tile using the tileset we grabbed earlier.
			TheTextureManager::Instance()->drawTile(
				tileset.name,												// Name of the texture
				tileset.margin,												// Margin of the tilsheet	(pixel space from the edge to first picture)
				tileset.spacing,											// Spacing of the tilesheet (pixel space between each picture)
				(j * m_tileSize) - x2,										// X position to draw the tile at
				(i * m_tileSize) - y2,										// Y position to draw the tile at
				m_tileSize,													// Width of tile
				m_tileSize,													// Height of tile
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,		// X Location of the tile on the tilesheet
				(id - (tileset.firstGridID - 1)) % tileset.numColumns);		// Y Location of the tile on the tilesheet
		}
	}
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
	m_tileIDs = data;
}

void TileLayer::setTileSize(int tileSize)
{
	m_tileSize = tileSize;
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	// Compares each tilesets firstgid value and returns the correct tileset
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}

	std::cout << "Dis not find tileset, returning empty tileset" << std::endl;
	Tileset t;
	return t;
}
