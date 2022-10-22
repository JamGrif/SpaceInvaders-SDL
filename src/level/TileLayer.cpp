#include "pch.h"
#include "level/TileLayer.h"

#include "core/SpriteManager.h"
#include "core/GameWindow.h"
#include "level/Level.h"

TileLayer::TileLayer(int tileSize)
	:m_tileSize(tileSize)
{
	// Number of columns and rows to fill the size of the game
	m_numColumns = (TheGameWindow::Instance()->getWindowWidth() / m_tileSize);
	m_numRows = (TheGameWindow::Instance()->getWindowHeight() / m_tileSize);

	//std::cout << "created tilelayer" << std::endl;

}

TileLayer::~TileLayer()
{
	//delete m_tileset;
}

/// <summary>
/// Update the tileset
/// </summary>
void TileLayer::updateLayer()
{
}

/// <summary>
/// Draw the tileset
/// </summary>
void TileLayer::renderLayer()
{
	// Loop through the number of columns and number of rows
	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			// Get current tile ID from the array
			int id = m_tileIDs[i][j];

			if (id == 0) // id == 0 is empty air / no tile sprite in that position
				continue;

			id--; // Decrement the ID so can draw the correct tile from the tilesheet (even if it is a position 0,0)

			// Use the drawTile function to copy across the correct tile using the tileset we grabbed earlier.
			TheSpriteManager::Instance()->drawSpriteTile(
				m_pTileset->name,
				(j * m_tileSize),											// X position to draw the tile at
				(i * m_tileSize),											// Y position to draw the tile at
				m_tileSize,													// Width of tile
				m_tileSize,													// Height of tile
				(id - (m_pTileset->firstGidID - 1)) / m_pTileset->numColumns,		// X Location of the tile on the tilesheet
				(id - (m_pTileset->firstGidID - 1)) % m_pTileset->numColumns);		// Y Location of the tile on the tilesheet
		}
	}
}
