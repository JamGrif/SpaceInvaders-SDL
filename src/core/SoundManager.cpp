#include "pch.h"
#include "core/SoundManager.h"

#include "SDL2_mixer/SDL_mixer.h"

#define FREQUENCY 22050
#define FORMAT AUDIO_S16
#define CHANNELS 2
#define CHUNK_SIZE 4096

#define VOLUME_MINIMUM 0
#define VOLUME_MAXIMUM 50

#define ALL_CHANNELS -1

SoundManager* SoundManager::s_pInstance = nullptr;

bool SoundManager::init()
{
	// Must be called to setup audio for the game (before sound can be used)
	Mix_OpenAudio(FREQUENCY, FORMAT, CHANNELS, CHUNK_SIZE);

	// Set initial volume
	Mix_Volume(ALL_CHANNELS, VOLUME_MAXIMUM);
	Mix_VolumeMusic(VOLUME_MAXIMUM);

	TheSoundManager::Instance()->loadSound("res/audio/playerShoot.wav", "playerShoot");
	TheSoundManager::Instance()->loadSound("res/audio/playerExplosion.wav", "playerExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/alienExplosion.wav", "alienExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/menuMouseOver.wav", "menuMouseOver");
	TheSoundManager::Instance()->loadMusic("res/audio/music.ogg", "music");

	return true;
}

void SoundManager::clean()
{
	// Loop through chunks and delete them
	for (auto const& [key, value] : m_sfxs)
	{
		Mix_FreeChunk(value);
	}
	m_sfxs.clear();

	// Loop through music and delete them
	for (const auto& [key, value] : m_music)
	{
		Mix_FreeMusic(value);
	}
	m_music.clear();

	Mix_CloseAudio();
	Mix_Quit();

	delete s_pInstance;
}

bool SoundManager::loadSound(const std::string& fileName, const std::string& id)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());

	if (!pChunk)
	{
		std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
		return false;
	}

	m_sfxs[id] = pChunk;
	return true;
}

bool SoundManager::loadMusic(const std::string& fileName, const std::string& id)
{
	Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());

	if (!pMusic)
	{
		std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
		return false;
	}

	m_music[id] = pMusic;
	return true;
}

void SoundManager::playMusic(const std::string& id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(const std::string& id, int loop)
{
	// First parameter is for the channel that the sound be played on. -1 tells SDL_mixer to play the sound on any available channel
	Mix_PlayChannel(ALL_CHANNELS, m_sfxs[id], loop);
}

/// <summary>
/// Toggle the Sound volume
/// </summary>
void SoundManager::toggleSound()
{
	m_bPlayingSound = !m_bPlayingSound;

	m_bPlayingSound ? Mix_Volume(ALL_CHANNELS, VOLUME_MAXIMUM) : Mix_Volume(ALL_CHANNELS, VOLUME_MINIMUM);
}

/// <summary>
/// Toggle the Music volume
/// </summary>
void SoundManager::toggleMusic()
{
	m_bPlayingMusic = !m_bPlayingMusic;

	m_bPlayingMusic ? Mix_VolumeMusic(VOLUME_MAXIMUM) : Mix_VolumeMusic(VOLUME_MINIMUM);
}
