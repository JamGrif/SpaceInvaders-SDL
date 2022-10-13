#pragma once
#include "level/BaseLayer.h"

struct Tileset;

/// <summary>
/// Only contains all the tilesets used by the level
/// Handles the updating and drawing of the tilesets
/// </summary>
class TileLayer :
    public BaseLayer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset>& tilesets);
	~TileLayer();

	virtual void updateLayer() override;
	virtual void renderLayer() override;

	void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }

	void setTileSize(int tileSize) { m_tileSize = tileSize; }

	Tileset getTilesetByID(int tileID) const;

private:
	// Number of columns and rows to draw tiles too, determined from size of window
	int m_numColumns;
	int m_numRows;

	// Pixel size of individual tile frame
	int m_tileSize;

	// Used for scrolling the map
	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset>& m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;
};

