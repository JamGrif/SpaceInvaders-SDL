#include "pch.h"
#include "core/SoundManager.h"



SoundManager* SoundManager::s_pInstance = nullptr;

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());

		if (pMusic == 0)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_music[id] = pMusic;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());

		if (pChunk == 0)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_sfxs[id] = pChunk;
		return true;
	}

	return false;
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playMusic(std::string id, int loop)
{
	// First parameter is for the channel that the sound be played on. -1 tells SDL_mixer to play the sound on any available channel
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}


SoundManager::SoundManager()
{
	// Must be called to setup audio for the game (before sound can be used)
	Mix_OpenAudio(
		22050,		// Frequency
		AUDIO_S16,	// Format
		2,			// Channels
		4096);		// Chunksize
}

SoundManager::SoundManager(const SoundManager&)
{

}

SoundManager& SoundManager::operator=(const SoundManager&)
{

}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}
