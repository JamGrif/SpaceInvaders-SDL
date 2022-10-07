#include "pch.h"
#include "gameobjects/TextObject.h"

#include "core/Renderer.h"

#include "SDL2_ttf/SDL_ttf.h"

static TTF_Font* g_pFont;
static bool g_bSetFont = false;


TextObject::TextObject()
{
}

TextObject::~TextObject()
{
}

void TextObject::loadObject(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::loadObject(pParams);

	if (!g_bSetFont)
	{
		g_pFont = TTF_OpenFont("res/text/04B_30__.ttf", 40);
		g_bSetFont = true;
	}

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
}

void TextObject::updateText(const std::string& newText)
{
	m_text = newText;

	SDL_Surface* textSurface = TTF_RenderText_Solid(g_pFont, m_text.c_str(), m_textColor);

	if (!textSurface)
		return;

	m_textTexture = SDL_CreateTextureFromSurface(TheRenderer::Instance()->getRendererPtr(), textSurface);

	SDL_FreeSurface(textSurface);

	SDL_QueryTexture(m_textTexture, NULL, NULL, &m_objectWidth, &m_objectHeight);

	m_textDimensions = { static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_objectWidth, m_objectHeight };
}
