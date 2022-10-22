#include "pch.h"
#include "level/LevelParser.h"

#include "core/SpriteManager.h"
#include "gameobjects/utility/GameObjectFactory.h"
#include "gameobjects/BaseGameObject.h"
#include "level/Level.h"
#include "level/TileLayer.h"

#include "Base64/base64.h"		// Decode the level data
#include "zlib/zlib.h"			// Decompress the level data
#include "tinyXML/tinyxml.h"	// Read the level data

#define LEVEL_PATH_PREFIX "res/levels/"
#define TILESET_PATH_PREFIX "res/levels/"
#define SPRITE_PATH_PREFIX "res/sprites/"

/// <summary>
/// Called whenever a .tmx file needs to be parsed at filepath
/// </summary>
Level* LevelParser::parseLevel(const std::string& filepath, std::vector<std::shared_ptr<BaseGameObject>>& allGameObjects)
{
	// Create the TinyXML document and load the map XML
	TiXmlDocument levelDocument;

	if (!levelDocument.LoadFile(LEVEL_PATH_PREFIX + filepath))
	{
		std::cout << levelDocument.ErrorDesc() << std::endl;
		return nullptr;
	}

	createdLevel = new Level();

	// Get the root node <map> </map>
	const TiXmlElement& pRoot = *levelDocument.RootElement();

	pRoot.Attribute("tilewidth", &m_tilePixelSize);
	pRoot.Attribute("width", &m_levelTileWidth);
	pRoot.Attribute("height", &m_levelTileHeight);

	// Parse any sprites
	std::vector<std::pair<std::string, std::string>> spritesToLoad;
	for (const TiXmlElement* e = pRoot.FirstChildElement()->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		// <properties> node
		if (strcmp(e->Value(), "property") == 0)
		{
			//std::pair<std::string, std::string> temp;
			//temp.first = SPRITE_PATH_PREFIX + std::string(e->Attribute("value"));
			//temp.second = e->Attribute("name");
			//spritesToLoad.emplace_back(SPRITE_PATH_PREFIX + std::string(e->Attribute("value")) , e->Attribute("name"));
			spritesToLoad.emplace_back(SPRITE_PATH_PREFIX + std::string(e->Attribute("value")), e->Attribute("name"));
		}


		//TheSpriteManager::Instance()->loadSprite(SPRITE_PATH_PREFIX + std::string(pPropertiesRoot.Attribute("value")), pPropertiesRoot.Attribute("name"));
	}
	parseSprites(spritesToLoad);

	// Parse any tileset
	for (const TiXmlElement* e = pRoot.FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		// <tileset> node
		if (strcmp(e->Value(), "tileset") == 0)
		{
			parseTilesets(*e);
		}
	}

	// Parse any layers
	for (const TiXmlElement* e = pRoot.FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		// <objectgroup> node
		if (strcmp(e->Value(), "objectgroup") == 0)
		{
			parseObjectLayer(*e, allGameObjects);
		}
		// <layer> node
		else if (strcmp(e->Value(), "layer") == 0)
		{
			parseTileLayer(*e);
		}
	}

	// .tmx file has been fully parsed, so return newly created level
	return createdLevel;
}

/// <summary>
/// Parse the <layer> </layer> node in the .tmx file
/// The TileLayer is the layer the tileset is drawn too in the level editor
/// Uses the Base64 and zlib libraries to decode and decompress the data
/// </summary>
void LevelParser::parseTileLayer(const TiXmlElement& pLayerRoot)
{
	// Create new TileLayer
	std::unique_ptr<TileLayer> pTileLayer = std::make_unique<TileLayer>(m_tilePixelSize);
	pTileLayer->addTileset(std::move(pTileset));

	// Will hold base64 decoded level data
	std::string decodedIDs; 

	// Search for <data> </data> and decode the text (the tile layer data in level editor)
	for (const TiXmlElement* e = pLayerRoot.FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (strcmp(e->Value(), "data") == 0)
		{
			// Retrieve the text
			const TiXmlText* text = e->FirstChild()->ToText();
			const std::string t = text->Value();

			// Use Base64 decoder to decode text
			decodedIDs = base64_decode(t);
		}
	}

	/*
		Level data text is decoded to a base64 decoded string, now use zlib library to decompress the data
	*/

	// Total number of tiles in level (times by sizeof an int)
	uLongf numGids = (m_levelTileWidth * m_levelTileHeight) * sizeof(int);

	// Uncompress the level data and find what tileset frame is in each level tile
	const std::vector<unsigned int> gids(numGids);
	uncompress((Bytef*)&gids.at(0), &numGids, (const Bytef*)decodedIDs.c_str(), static_cast<uLong>(decodedIDs.size()));

	// The gids vector now contains all the level tiles and which tileset frame id it uses
	// so now to set the size of the data vector so it can be filled with the tile IDs

	/*
		Level data is now fully decompressed, now to fill out level data
	*/

	// Holds the decoded and uncompressed tile data for each level tile
	std::vector<std::vector<int>> tiledata;

	const std::vector<int> layerRow(m_levelTileWidth);

	for (int j = 0; j < m_levelTileHeight; j++)
	{
		tiledata.push_back(layerRow);
	}

	// Now to fill our data array with the correct values
	for (int rows = 0; rows < m_levelTileHeight; rows++)
	{
		for (int cols = 0; cols < m_levelTileWidth; cols++)
		{
			// Set each level tile a tileset frame ID
			tiledata.at(rows).at(cols) = gids.at(rows * m_levelTileWidth + cols);
		}
	}

	// Finally, set this layers tile data
	pTileLayer->setTileIDs(tiledata);

	// Push this tilelayer layer into level layer vector
	//pLayers->push_back(pTileLayer);
	createdLevel->addTileLayer(std::move(pTileLayer));
}

/// <summary>
/// Parse the <objectgroup> </objectgroup> node in the .tmx file
/// The object layer is all the objects added in the level editor
/// The object layer handles all the updating and drawing of only the objects created from this layer
/// </summary>
void LevelParser::parseObjectLayer(const TiXmlElement& pObjectGroupRoot, std::vector<std::shared_ptr<BaseGameObject>>& allGameObjects)
{
	// Loop through each <object> node in <objectgroup> node, creating the respective gameobject type and filling it out
	for (const TiXmlElement* e = pObjectGroupRoot.FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		// Ensure node is a <object> node
		if (strcmp(e->Value(), "object") != 0)
			continue;

		// Create object of specific type("class")
		//BaseGameObject* pGameObject = TheGameObjectFactory::Instance()->createGameObject(e->Attribute("class"));
		std::shared_ptr<BaseGameObject> pGameObject = TheGameObjectFactory::Instance()->createGameObject(e->Attribute("class"));
		if (!pGameObject)
			continue; // class type not registered in factory

		std::unique_ptr<LoaderParams> tempLoaderParams = std::make_unique<LoaderParams>();

		// Get the initial x, y and class values (All objects have these properties)
		e->Attribute("x", &tempLoaderParams->xPos);
		e->Attribute("y", &tempLoaderParams->yPos);
		tempLoaderParams->classType = e->Attribute("class");

		// Loop through each <properties> node of an object
		for (const TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
		{
			// Ensure node is a <properties node>
			if (strcmp(properties->Value(), "properties") != 0)
				continue;
			
			// Loop through each <property> node of an objects properties
			for (const TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
			{
				// Ensure node is a <property> node
				if (strcmp(property->Value(), "property") != 0)
					continue;

				// Determine what each <property> node is and then assign it to associated LoaderParam value
				if (strcmp(property->Attribute("name"), "numFrames") == 0)
					property->Attribute("value", &tempLoaderParams->numFrames);
	
				else if (strcmp(property->Attribute("name"), "textureID") == 0)
					tempLoaderParams->textureID = property->Attribute("value");
				
				else if (strcmp(property->Attribute("name"), "selectCallbackID") == 0)
					property->Attribute("value", &tempLoaderParams->selectCallbackID);
				
				else if (strcmp(property->Attribute("name"), "animationSpeed") == 0)
					property->Attribute("value", &tempLoaderParams->animationSpeed);
				
				else if (strcmp(property->Attribute("name"), "livesRequired") == 0)
					property->Attribute("value", &tempLoaderParams->livesRequired);
				
				else if (strcmp(property->Attribute("name"), "text") == 0)
					tempLoaderParams->text = property->Attribute("value");
				
				else if (strcmp(property->Attribute("name"), "checkboxStateCallbackID") == 0)
					property->Attribute("value", &tempLoaderParams->checkboxStateCallbackID);
				
				else if (strcmp(property->Attribute("name"), "scoreWorth") == 0)
					property->Attribute("value", &tempLoaderParams->scoreWorth);
				
				else if (strcmp(property->Attribute("name"), "textCallbackID") == 0)
					property->Attribute("value", &tempLoaderParams->textCallbackID);
				
				else if (strcmp(property->Attribute("name"), "textSize") == 0)
					property->Attribute("value", &tempLoaderParams->textSize);

				else if (strcmp(property->Attribute("name"), "movementSpeed") == 0)
				{
					double x;
					property->Attribute("value", &x);
					tempLoaderParams->movementSpeed = static_cast<float>(x);
				}
			}
		}

		// Now that LoaderParams is filled out, use it to load the values of the gameobject
		pGameObject->loadObject(tempLoaderParams);

		// Put the new object into the total gameobject vector
		allGameObjects.push_back(pGameObject);
	}
}

/// <summary>
/// Parse the <properties> </properties> node in the .tmx file
/// Creates all the sprites used in the level file
/// Sprites to load are specified in the map properties in the level editor
/// </summary>
void LevelParser::parseSprites(const std::vector<std::pair<std::string, std::string>>& spritesToLoad)
{
	TheSpriteManager::Instance()->loadSprite(spritesToLoad);
}

/// <summary>
/// Parse the <tileset> </tileset> node in the .tmx file
/// Creates all the tilesets used in the level file
/// Tilesets to load are specified in the level editor
/// </summary>
void LevelParser::parseTilesets(const TiXmlElement& pTilesetRoot)
{
	// Load the tileset (the filepath is the same as the .tmx file path)
	TheSpriteManager::Instance()->loadSprite(TILESET_PATH_PREFIX + std::string(pTilesetRoot.FirstChildElement()->Attribute("source")), pTilesetRoot.Attribute("name"));

	// Create a tileset object and fill it out
	pTileset = std::make_unique<Tileset>();

	// Assign values to the Tileset members from the .tmx file
	pTileset->name = pTilesetRoot.Attribute("name");
	pTilesetRoot.Attribute("firstgid",						&pTileset->firstGidID);
	pTilesetRoot.Attribute("tilewidth",						&pTileset->tileWidth);
	pTilesetRoot.Attribute("tileheight",					&pTileset->tileHeight);
	pTilesetRoot.Attribute("columns",						&pTileset->numColumns);
	pTilesetRoot.Attribute("spacing",						&pTileset->spacing);
	pTilesetRoot.Attribute("margin",						&pTileset->margin);
	pTilesetRoot.FirstChildElement()->Attribute("width",	&pTileset->width);
	pTilesetRoot.FirstChildElement()->Attribute("height",	&pTileset->height);
}
