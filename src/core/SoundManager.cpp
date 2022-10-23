#include "pch.h"
#include "core/SoundManager.h"

static constexpr uint16_t FREQUENCY		 = 22050;
static constexpr uint16_t FORMAT		 = AUDIO_S16;
static constexpr uint8_t  CHANNELS		 = 2;
static constexpr uint16_t CHUNK_SIZE	 = 4096;

static constexpr uint8_t  VOLUME_MINIMUM = 0;
static constexpr uint8_t  VOLUME_MAXIMUM = 50;

static constexpr int8_t   ALL_CHANNELS	 = -1;

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
	TheSoundManager::Instance()->loadSound("res/audio/playerShoot.wav",		"playerShoot");
	TheSoundManager::Instance()->loadSound("res/audio/alienShoot.wav",		"alienShoot");
	TheSoundManager::Instance()->loadSound("res/audio/playerExplosion.wav", "playerExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/gameOver.wav",		"gameOver");
	TheSoundManager::Instance()->loadSound("res/audio/alienExplosion.wav",	"alienExplosion");
	TheSoundManager::Instance()->loadSound("res/audio/roundReset.wav",		"roundReset");
	TheSoundManager::Instance()->loadSound("res/audio/alienBossMove.wav",	"alienBossMove", ALIEN_BOSS_CHANNEL);
	TheSoundManager::Instance()->loadSound("res/audio/blockBreak.wav",		"blockBreak");
	TheSoundManager::Instance()->loadSound("res/audio/gameStart.wav",		"gameStart");
	TheSoundManager::Instance()->loadMusic("res/audio/music.ogg",			"music");

	return true;
}

/// <summary>
/// Clean the SoundManager systems
/// </summary>
void SoundManager::clean()
{
	// Delete all sound effect and music objects
	m_soundEffectObjects.clear();
	m_musicObjects.clear();

	// Close SDL_mixer
	Mix_CloseAudio();
	Mix_Quit();
}

/// <summary>
/// Load sound at filepath and assign an id to it
/// </summary>
bool SoundManager::loadSound(const std::string& filepath, const std::string& id, int8_t chosenChannel)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(filepath.c_str());

	if (!pChunk)
	{
		std::cout << "Could not load sound with filepath:" << filepath << " -> " << Mix_GetError() << std::endl;
		return false;
	}

	// If Mix_Chunk was created successfully, create sound object and add to map
	std::unique_ptr<SoundEffectObject> sound = std::make_unique<SoundEffectObject>(pChunk, chosenChannel);

	m_soundEffectObjects.insert({id, std::move(sound)});
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
		std::cout << "Could not load music with filepath:" << filepath << " -> " << Mix_GetError() << std::endl;
		return false;
	}

	// If Mix_Music was created successfully, create music object and add to map
	std::unique_ptr<MusicObject> music = std::make_unique<MusicObject>(pMusic);

	m_musicObjects.insert({id, std::move(music)});
	return true;
}

/// <summary>
/// Play specified sound effect, using the id assigned to choose it
/// </summary>
void SoundManager::playSound(const std::string& id, bool loop)
{
	int loopFlag = 0;
	if (loop)
	{
		loopFlag = -1;
	}

	try
	{
		Mix_PlayChannel(m_soundEffectObjects.at(id)->getChannel(), m_soundEffectObjects.at(id)->getSfxChunk(), loopFlag);
	}
	catch (const std::exception& e)
	{
		std::cout << "Failed to play sound with id " << id << " -> " << e.what() << " -> " << __FUNCTION__ << std::endl;
	}
	
}

/// <summary>
/// Play specified music, using the id assigned to choose it
/// </summary>
void SoundManager::playMusic(const std::string& id, bool loop)
{
	try
	{
		Mix_PlayMusic(m_musicObjects.at(id)->getMusicChunk(), loop);
	}
	catch (const std::exception& e)
	{
		std::cout << "Failed to play music with id " << id << " -> " << e.what() << " -> " << __FUNCTION__ << std::endl;
	}
}

/// <summary>
/// Stop any sound effects playing on specified channel
/// </summary>
void SoundManager::stopSound(int8_t channel)
{
	Mix_HaltChannel(channel);
}

/// <summary>
/// Stop sound effects playing on all channels
/// </summary>
void SoundManager::stopAllSounds()
{
	Mix_HaltChannel(ALL_CHANNELS);
}

/// <summary>
/// Stop any music playing
/// </summary>
void SoundManager::stopMusic()
{
	Mix_HaltMusic();
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
