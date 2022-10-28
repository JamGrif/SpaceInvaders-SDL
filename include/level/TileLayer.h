#pragma once

// Holds any information needed to know about the tileset
// Passed into the parser when its time to load the map
struct Tileset
{
	std::string name;			// Name of tileset in editor
	int32_t firstGidID	= 0;	// First global tile ID of this tileset (This ID maps to the first tile in this tileset)
	int32_t tileWidth	= 0;	// Pixel size of an individual tile width
	int32_t tileHeight	= 0;	// Pixel size of an individual tile height
	int32_t numColumns	= 0;	// Number of tile frames in a row
	int32_t spacing		= 0;	// Pixel space between each sprite frame
	int32_t margin		= 0;	// Pixel space from the edge to first sprite frame
	int32_t width		= 0;	// Total pixel width of complete sprite
	int32_t height		= 0;	// Total pixel height of complete sprite
};

/// <summary>
/// Only contains all the tilesets used by the level
/// Handles the updating and drawing of the tilesets
/// </summary>
class TileLayer
{
public:
	TileLayer(int tileSize);
	~TileLayer();

	void		updateLayer();
	void		renderLayer();

	void		addTileset(std::unique_ptr<Tileset> t) { m_pTileset = std::move(t); }

	void		setTileIDs(const std::vector<std::vector<uint16_t>>& data) { m_tileIDs = data; }

	void		setTileSize(uint8_t tileSize) { m_tileSize = tileSize; }

private:
	// Pixel size of individual tile frame
	uint8_t		m_tileSize;

	// Number of columns and rows to draw tiles too, determined from size of window
	const uint16_t	m_numColumns;
	const uint16_t	m_numRows;

	std::unique_ptr<Tileset> m_pTileset;
	std::vector<std::vector<uint16_t>> m_tileIDs;
};

