#include "pch.h"
#include "states/utility/StateParser.h"

#include "tinyxml.h"

#include "core/TextureManager.h"
#include "gameobjects/GameObject.h"
#include "gameobjects/utility/GameObjectFactory.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs)
{
	// Create the XML document
	TiXmlDocument xmlDoc;

	// Load the state file
	if (!xmlDoc.LoadFile(stateFile))
	{
		std::cerr << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}

	// Get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement(); // Grab the root node of the XML file - <STATES> , all other nodes in the file are children of this root node

	// Pre declare the state root node
	TiXmlElement* pStateRoot = 0;

	// Get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) // Get root node of the state we are currently parsing
	{
		if (e->Value() == stateID) // Goes through each direct child of the root node and checks if its name is the same as stateID
		{
			pStateRoot = e; // Once it finds the correct node, it assigns it to pStateRoot. We now have the root node of the state we want to parse
		}
	}

	// Now we have a pointer to the root node of our state, we can start to grab the values from it (The textures and GameObjects the state uses)

	// First, want to load the textures from the file, so look for the <TEXTURE> node using the children of the pStateRoot object

	// Pre declare the texture root
	TiXmlElement* pTextureRoot = 0;

	// Get the root of the texture elements
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}

	// Now parse the textures
	parseTextures(pTextureRoot, pTextureIDs); // Once the <TEXTURE> node is found, we can pass it to this function

	// As the states textures have been parsed, can then move onto searching for the <OBJECTS> node

	// Pre declare the object root node
	TiXmlElement* pObjectRoot = 0;

	// Get the root node and assign it to pObjectRoot
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}

	// Now parse the objects
	parseObjects(pObjectRoot, pObjects);

	//std::cout << "Finished parse" << std::endl;

	return true;
}

// Creates objects using the GameObjectFactory function and reads the <OBJECTS> part of the XML file
void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects)
{
	// Loop through all elements of <OBJECTS>
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		// Get all the values needed from the current node.
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		// Create GameObject* class using the factory
		GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type")); // "type" is the one specified in XML and is used to create the correct object from the factory

		// Uses the load function to set the desired values loaded from the XML file
		pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));

		// pObjects is a pointer to the current state's object vector
		pObjects->push_back(pGameObject);
	}
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		// Get the filename and ID attributes from each of the texture values in the file
		std::string filenameAttributes = e->Attribute("filename");	// Example: ( filename="res/sprites/button.png" )
		std::string idAttribute = e->Attribute("ID");				// Example: ( ID="playbutton" )

		pTextureIDs->push_back(idAttribute); // Push into texture list
		TheTextureManager::Instance()->load(filenameAttributes, idAttribute); // Load texture
	}
}
