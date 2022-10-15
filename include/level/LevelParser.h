#pragma once

class Level;
class BaseLayer;
class TiXmlElement;
struct Tileset;

/// <summary>
/// Parser for a .tmx file, creating and filling out a level object from it with its associative layers
/// </summary>
class LevelParser
{
public:

	Level* parseLevel(const std::string& filepath);

private:

	// Layers
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<BaseLayer*>* pLayers, const std::vector<Tileset>* pTilesets);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<BaseLayer*>* pLayers);

	// Sprites
	void parseSprites(TiXmlElement* pSpriteRoot);
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

	// Dimensions, in pixels, of an individual tile
	int m_tilePixelSize;

	// Dimensions, in tiles, of the entire .tmx file
	int m_levelTileWidth;
	int m_levelTileHeight;
};

