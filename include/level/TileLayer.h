#pragma once
#include "BaseLayer.h"

struct Tileset;

// TileLayer is made up entirely of tiles and does not contain anything else
class TileLayer :
    public BaseLayer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset>& tilesets);
	~TileLayer();

	virtual void updateLayer();
	virtual void renderLayer();

	void setTileIDs(const std::vector<std::vector<int>>& data);

	void setTileSize(int tileSize);

	Tileset getTilesetByID(int tileID);

private:
	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	// Used for scrolling the map
	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset>& m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;
};

