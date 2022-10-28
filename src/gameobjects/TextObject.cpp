#include "pch.h"
#include "gameobjects/TextObject.h"

#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

#include "core/Renderer.h"
#include "core/TextManager.h"
#include "core/SpriteManager.h"

TextObject::TextObject()
	:m_textCallback(nullptr), m_textCallbackID(0), m_textColor({0,255,0})
{
}

TextObject::~TextObject()
{
}

/// <summary>
/// Set all values in TextObject class and parent classes
/// </summary>
void TextObject::loadObject(std::unique_ptr<LoaderParams> pParams)
{
	m_textCallbackID = pParams->textCallbackID;

	// Set this objects font
	m_thisFont = TheTextManager::Instance()->getFont(pParams->textSize);

	// Set the current text
	m_text = pParams->text;

	SDLGameObject::loadObject(std::move(pParams));

	// As a TextObject isn't assigned a filepath or ID in level editor,
	// it needs to retrieve a free ID from SpriteManager to identify its Sprite object
	m_objectTextureID = std::to_string(TheSpriteManager::Instance()->getNextFreeID());

	updateText(m_text);
}

/// <summary>
/// Draw the text
/// </summary>
void TextObject::drawObject()
{
	SpriteManager::Instance()->drawSpriteText(m_objectTextureID, m_objectAttributes);
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
void TextObject::updateObject()
{
	SDLGameObject::updateObject();

	// If the TextObject uses a callback function, it means it copies a value from somewhere else in the program
	if (m_textCallbackID)
	{
		// Update text only if changed
		if (m_text != m_textCallback())
			updateText(m_textCallback());
	}
}

/// <summary>
/// Update the rendered text to specified value
/// </summary>
void TextObject::updateText(const std::string& newText)
{
	// Create the new SDL_Texture object with the new text value
	SDL_Surface* textSurface = TTF_RenderText_Solid(const_cast<TTF_Font*>(m_thisFont.lock()->getTTF_Font()), newText.c_str(), m_textColor);
	if (!textSurface)
		return;

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), textSurface);
	SDL_FreeSurface(textSurface);
	if (!textTexture)
		return;

	// Store the new text
	m_text = newText;

	// If first time creating sprite at m_objectTextureID, create the Sprite object
	if (TheSpriteManager::Instance()->getSpriteViaID(m_objectTextureID).expired())
		TheSpriteManager::Instance()->createSprite(textTexture, m_objectTextureID, SpriteType::STATE_SPRITE);
	// Otherwise, simply swap out the SDL_Texture with the newly created one
	else
		TheSpriteManager::Instance()->getSpriteViaID(m_objectTextureID).lock()->changeTexture(textTexture);

	// Update m_objectAttributes for rendering
	m_objectAttributes.x = static_cast<int>(m_position.getX());
	m_objectAttributes.y = static_cast<int>(m_position.getY());
	TheSpriteManager::Instance()->getSpriteViaID(m_objectTextureID).lock()->getSpriteDimensions(m_objectAttributes);
}
