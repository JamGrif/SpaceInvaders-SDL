#include "pch.h"
#include "core/TextManager.h"

#include "SDL2/SDL.h"

static constexpr int8_t INITIALIZE_SUCCESS = 0;
static const char* FONTPATH = "res/text/04B_30__.ttf";

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
	m_loadedFonts.clear();
	
	TTF_Quit();
}

/// <summary>
/// Retrieve font object of specified size, creating and storing it if doesn't currently exist
/// </summary>
std::weak_ptr<FontData> TextManager::getFont(uint8_t textSize)
{
	// If font of size textSize doesn't already exist, create it, add to map and return it
	if (!m_loadedFonts.count(textSize))
	{
		TTF_Font* font = TTF_OpenFont(FONTPATH, textSize);
		if (!font)
			return {};

		m_loadedFonts.insert({ textSize, std::make_shared<FontData>(font, textSize) });
		return m_loadedFonts[textSize];
	}

	// Font does exist of textSize so return it
	return m_loadedFonts.at(textSize);
}
