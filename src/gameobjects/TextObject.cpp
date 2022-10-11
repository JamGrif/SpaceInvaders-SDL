#include "pch.h"
#include "gameobjects/TextObject.h"

#include "core/Renderer.h"

#include "core/TextManager.h"
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

#define FONTPATH "res/text/04B_30__.ttf"



TextObject::TextObject()
{
	m_textColor = { 0, 255, 0 };
}

TextObject::~TextObject()
{
}

void TextObject::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	m_textCallbackID = pParams->textCallbackID;
	m_textSize = pParams->textSize;

	// Set this objects font
	m_thisFont = TheTextManager::Instance()->getFont(m_textSize);

	// Set the current text
	updateText(pParams->text);
}

void TextObject::drawObject()
{
	SDL_RenderCopy(TheRenderer::Instance()->getRendererPtr(), m_textTexture, NULL, &m_textDimensions);
}

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

void TextObject::updateText(const std::string& newText)
{
	m_text = newText;

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_thisFont, m_text.c_str(), m_textColor);

	if (!textSurface)
		return;

	m_textTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), textSurface);

	SDL_FreeSurface(textSurface);

	SDL_QueryTexture(m_textTexture, NULL, NULL, &m_objectWidth, &m_objectHeight);

	m_textDimensions = { static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_objectWidth, m_objectHeight };
}
