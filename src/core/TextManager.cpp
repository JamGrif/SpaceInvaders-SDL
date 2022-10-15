#include "pch.h"
#include "core/TextManager.h"

#include "SDL2/SDL.h"

#define INITIALIZE_SUCCESS 0
#define FONTPATH "res/text/04B_30__.ttf"

TextManager* TextManager::s_pInstance = nullptr;

/// <summary>
/// Initializes the TextManager systems
/// </summary>
bool TextManager::init()
{
	if (TTF_Init() != INITIALIZE_SUCCESS)
	{
		std::cout << "TTF could not initialize - " << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}

/// <summary>
/// Clean up the TextManager systems
/// </summary>
void TextManager::clean()
{
	// Loop through and delete all open fonts
	for (auto& [key, value] : m_loadedFonts)
	{
		TTF_CloseFont(value);
	}

	TTF_Quit();
}

/// <summary>
/// Retrieve font object of specified size, creating and storing it if doesn't currently exist
/// </summary>
TTF_Font* TextManager::getFont(int textSize)
{
	// If font of size textSize doesn't already exist, create it, add it to map and return it
	if (!m_loadedFonts.count(textSize))
	{
		TTF_Font* font = TTF_OpenFont(FONTPATH, textSize);
		m_loadedFonts.insert({ textSize, font });
		return font;
	}

	// Font does exist of textSize so return it
	return m_loadedFonts.at(textSize);
}


