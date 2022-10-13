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

/// <summary>
/// Initializes the SoundManager systems
/// </summary>
bool SoundManager::init()
{
	// Must be called to setup audio for the game (before sound can be used)
	Mix_OpenAudio(FREQUENCY, FORMAT, CHANNELS, CHUNK_SIZE);

	// Set initial volume
	Mix_Volume(ALL_CHANNELS, VOLUME_MAXIMUM);
	Mix_VolumeMusic(VOLUME_MAXIMUM);

	// Load all sounds and music used in the program
	TheSoundManager::Instance()->loadSound("res/audio/playerShoot.wav", "playerShoot");
	TheSoundManager::Instance()->loadSound("res/audio/playerExplosion.wav", "playerExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/alienExplosion.wav", "alienExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/menuMouseOver.wav", "menuMouseOver");
	TheSoundManager::Instance()->loadMusic("res/audio/music.ogg", "music");

	return true;
}

/// <summary>
/// Clean the SoundManager systems
/// </summary>
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

	// Close SDL_mixer
	Mix_CloseAudio();
	Mix_Quit();
}

/// <summary>
/// Load sound at filepath and assign an id to it
/// </summary>
bool SoundManager::loadSound(const std::string& filepath, const std::string& id)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(filepath.c_str());

	if (!pChunk)
	{
		std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
		return false;
	}

	m_sfxs[id] = pChunk;
	return true;
}

/// <summary>
/// Load music at filepath and assign an id to it
/// </summary>
bool SoundManager::loadMusic(const std::string& filepath, const std::string& id)
{
	Mix_Music* pMusic = Mix_LoadMUS(filepath.c_str());

	if (!pMusic)
	{
		std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
		return false;
	}

	m_music[id] = pMusic;
	return true;
}

/// <summary>
/// Play specified sound effect, using the id assigned to choose it
/// </summary>
void SoundManager::playSound(const std::string& id, int loop)
{
	Mix_PlayChannel(ALL_CHANNELS, m_sfxs[id], loop);
}

/// <summary>
/// Play specified music, using the id assigned to choose it
/// </summary>
void SoundManager::playMusic(const std::string& id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

/// <summary>
/// Toggle the sound effect volume between on and off
/// </summary>
void SoundManager::toggleSoundEffects()
{
	m_bPlayingSound = !m_bPlayingSound;

	m_bPlayingSound ? Mix_Volume(ALL_CHANNELS, VOLUME_MAXIMUM) : Mix_Volume(ALL_CHANNELS, VOLUME_MINIMUM);
}

/// <summary>
/// Toggle the music volume between on and off
/// </summary>
void SoundManager::toggleMusic()
{
	m_bPlayingMusic = !m_bPlayingMusic;

	m_bPlayingMusic ? Mix_VolumeMusic(VOLUME_MAXIMUM) : Mix_VolumeMusic(VOLUME_MINIMUM);
}
