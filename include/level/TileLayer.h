#pragma once

struct Tileset;

/// <summary>
/// Only contains all the tilesets used by the level
/// Handles the updating and drawing of the tilesets
/// </summary>
class TileLayer
{
public:
	TileLayer(int tileSize);
	~TileLayer();

	void updateLayer();
	void renderLayer();

	void addTileset(std::unique_ptr<Tileset> t) { m_pTileset = std::move(t); }

	void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }

	void setTileSize(int tileSize) { m_tileSize = tileSize; }

private:
	// Number of columns and rows to draw tiles too, determined from size of window
	int m_numColumns;
	int m_numRows;

	// Pixel size of individual tile frame
	int m_tileSize;

	std::unique_ptr<Tileset> m_pTileset;
	std::vector<std::vector<int>> m_tileIDs;
};

