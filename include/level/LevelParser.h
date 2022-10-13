#pragma once

class Level;
class BaseLayer;
class TiXmlElement;
struct Tileset;

/// <summary>
/// Parser for a .tmx file, creating and filling out a level object from it
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
	void parseTextures(TiXmlElement* pTextureRoot);
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

	int m_tileSize;
	int m_width;
	int m_height;
};

