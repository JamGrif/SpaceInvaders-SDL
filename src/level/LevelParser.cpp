#include "pch.h"
#include "level/LevelParser.h"

#include "tinyxml.h"
#include "level/Level.h"
#include "core/TextureManager.h"
#include "gameobjects/utility/GameObjectFactory.h"

#include "level/TileLayer.h"
#include "level/ObjectLayer.h"
#include "gameobjects/GameObject.h"

#include "base64.h"
#include "zlib.h"
#include "zconf.h"

Level* LevelParser::parseLevel(const char* levelFile)
{
	// Create the TinyXML document and load the map XML
	TiXmlDocument levelDocument;

	if (!levelDocument.LoadFile(levelFile))
	{
		std::cout << "Couldn't find doucment" << std::endl;
		std::cout << levelDocument.ErrorDesc() << std::endl;
	}

	// Create the level object
	Level* pLevel = new Level();

	// Get the root node
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	// Know that properties is the first child of the root
	TiXmlElement* pProperties = pRoot->FirstChildElement();

	// Parse the textures needed for this level, which has been added to properties
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			parseTextures(e);
		}
	}

	// Parse the tileset
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	// Parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers());
			}
			else if (e->FirstChildElement()->Value() == std::string("data"))
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
			}
		}
	}

	
	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	// First add the tileset to texture manager
	TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"));

	// Create a tileset object and fill it out
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");

	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);


}

// The tile IDs are compressed and encoded in the .tmx file.
// Uses the Base64 and zlib libraries to help decode and decompress the data
void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets)
{
	// Create new TileLayer instance
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

	// Tile data
	std::vector<std::vector<int>> data; // Holds the decoded and uncompressed tiledata

	std::string decodedIDs; // base64 decoded information
	TiXmlElement* pDataNode = nullptr;

	// Search for the node that is needed (data node)
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	// Once correct node is found, can get the text from within it (the encoded/compressed data)
	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		// Use the Base64 decoder to decode it
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// The decodedIDs variable is now a base64 decoded string
	// Now to use the zlib library to decompress the data

	// Uncompress zlib compression
	uLongf numGids = m_width * m_height * sizeof(int);

	std::vector<unsigned int> gids(numGids);

	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	// The ids vector now contains all of the tile IDs
	// Now to set the size of the data vector so it can be filled with the tile IDs
	std::vector<int> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	// Now to fill our data array with the correct values
	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[rows * m_width + cols];
		}
	}

	

	// Finally, set this layers tile data and then push the layer into the layers array of the Level
	pTileLayer->setTileIDs(data);
	pLayers->push_back(pTileLayer);
}

// Gets the texture values from the xml file and adds them to TextureManager
void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"));
}


void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers)
{
	// Create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();

	//std::cout << pObjectElement->FirstChildElement()->Value() << std::endl;;

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		
		//std::cout << e->Value() << std::endl;
		if (e->Value() == std::string("object"))
		{
			
			int x, y, width, height, numFrames, callbackID, animSpeed;
			std::string textureID;

			// Get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);

			GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("class")); // ----

			// Get the property values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames")) // Check for the name of the property rather than grabbing the attribute directly
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == std::string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == std::string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Attribute("name") == std::string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (e->Attribute("name") == std::string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
						}
					}
				}
			}
			
			// Create the object just like the state parser
			pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));

			// Add it to this layers game object array
			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}

	// Once loaded all the objects for this layer, we can push it into our level layer array
	pLayers->push_back(pObjectLayer);
	
}
