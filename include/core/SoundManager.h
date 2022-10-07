#pragma once


#include "SDL2_mixer/SDL_mixer.h"

//enum sound_type
//{
//	SOUND_MUSIC = 0,
//	SOUND_SFX = 1
//};

// .ogg for music | .wav for sound effects
class SoundManager
{
public:
	void init();
	void clean();

	bool loadSound(const std::string& fileName, const std::string& id);
	bool loadMusic(const std::string& fileName, const std::string& id);

	void playSound(const std::string& id, int loop = false);
	void playMusic(const std::string& id, int loop = false);

	static SoundManager* Instance() // Instance Get
	{
		if (!s_pInstance)
			s_pInstance = new SoundManager();
		return s_pInstance;
	}

private:
	static SoundManager* s_pInstance; 

	std::unordered_map<std::string, Mix_Chunk*> m_sfxs;		// Mix_Chunk used for sound effects only
	std::unordered_map<std::string, Mix_Music*> m_music;	// Mix_Music used for music tracks only

	SoundManager() {};									// Prevent construction
	SoundManager(const SoundManager&) {};				// Prevent construction by copying
	SoundManager& operator=(const SoundManager&) {};	// Prevent assignment
	~SoundManager() {};									// Prevent unwanted destruction
};
typedef SoundManager TheSoundManager;

