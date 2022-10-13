#pragma once

struct SDL_Texture;
struct SDL_Rect;

/// <summary>
/// Encapsulates an SDL_Texture object and provides utility functions for it
/// Created and destroyed by SpriteManager
/// </summary>
class Sprite
{
public:
	Sprite(SDL_Texture* texture, const std::string& fileName, const std::string& id);
	~Sprite();

	void				setUpIndividualSpriteDimensions(int numFrames);

	inline SDL_Texture* getTexturePtr() { return m_texture; }
	inline std::string& getFileName() { return m_fileName; }
	inline std::string& getID() { return m_id; }

	const SDL_Rect*		getTotalDimensions() { return m_totalSpriteDimensions; };
	const SDL_Rect*		getIndividualDimensions() { return m_indivdualSpriteDimension; }

private:
	SDL_Texture* m_texture;

	std::string m_fileName;
	std::string m_id;

	SDL_Rect* m_indivdualSpriteDimension;
	SDL_Rect* m_totalSpriteDimensions;
};
