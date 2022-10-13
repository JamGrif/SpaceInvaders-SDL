#include "pch.h"
#include "gameobjects/TextObject.h"

#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

#include "core/Renderer.h"
#include "core/TextManager.h"

#define FONTPATH "res/text/04B_30__.ttf"

TextObject::TextObject()
	:m_textCallback(nullptr), m_textCallbackID(0), m_thisFont(nullptr), m_textTexture(nullptr),
	m_textDimensions({0,0,0,0}), m_textColor({0,255,0})
{
}

TextObject::~TextObject()
{
}

/// <summary>
/// Set all values in TextObject class and parent classes
/// </summary>
void TextObject::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_textCallbackID = pParams->textCallbackID;

	// Set this objects font
	m_thisFont = TheTextManager::Instance()->getFont(pParams->textSize);

	// Set the current text
	updateText(pParams->text);
}

/// <summary>
/// Draw the text
/// </summary>
void TextObject::drawObject()
{
	SDL_RenderCopy(TheRenderer::Instance()->getRendererPtr(), m_textTexture, NULL, &m_textDimensions);
}

/// <summary>
/// Call parent class update function and update values used in this class
/// </summary>
void TextObject::updateObject()
{
	SDLGameObject::updateObject();

	// If the TextObject uses a callback function, it means it copies a value from somewhere else in the program
	if (m_textCallbackID != 0)
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
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_thisFont, newText.c_str(), m_textColor);
	if (!textSurface)
		return;

	m_textTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), textSurface);
	SDL_FreeSurface(textSurface);
	if (!m_textTexture)
		return;

	m_text = newText;

	// Update dimensions of texture object as text has changed
	SDL_QueryTexture(m_textTexture, NULL, NULL, &m_objectWidth, &m_objectHeight);
	m_textDimensions = { static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_objectWidth, m_objectHeight };
}
