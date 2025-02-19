#include "Sound.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>

SoundManager::SoundManager()
{
    std::cout << "[*] Initializing Audio.\n";
    if (0 != SDL_Init(SDL_INIT_AUDIO))
    {
        std::cout << "[!] SDL_Init Audio did not return 0 code.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    if(0 > Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096))
    {
        std::cout << "[!] Mix_OpenAudio did not return 0 code./n" << Mix_GetError() << std::endl;
        exit(1);
    }


    
    LoadSoundEffect("player_primary_fire", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/cinematic-wind-swoosh-1471.wav");
    LoadSoundEffect("player_secondary_fire", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/fast-air-zoom-2625.wav");
    LoadSoundEffect("player_secondary_fire_impact", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/falling-on-foil-748.wav");
    LoadSoundEffect("player_hit", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/player_hit.wav");
    LoadSoundEffect("player_shield_activate", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/fast-air-zoom-2625.wav");
    LoadSoundEffect("player_shield_hit", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/jade-drum.wav");
    LoadSoundEffect("dash_sound", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/whoosh-wind-sweep-2632.wav");


    LoadSoundEffect("item_collection_sound", "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/sounds/unlock-new-item-game-notification-254.wav");
    

    music_map["first_level_song"] = "G:/My Drive/PC-Space/Video-Game-Stuff/Zephyr-the-Avenger/assets/soundsmusic/ChrisChristodoulou-TheyMightAsWellBeDeadROR2_SurvivorsoftheVoid(2022).mp3";
}

SoundManager::~SoundManager()
{
    std::cout << "[*] Turning off the SDL Audio./n";

    for (auto& pair : sound_effects_map)
    {
        Mix_FreeChunk(pair.second);
    }
    
    Mix_CloseAudio();
    Mix_Quit();
}



void SoundManager::PlaySound(const char* sound_map_key)
{
    if (1 == Mix_Playing(-1))
    {
        std::cout << "[*] A sound is already playing, doing nothing.";
        //return;
    }
    
    

    std::cout << "[*] Playing Sound Effect" << sound_effects_map[sound_map_key] << std::endl;
    // Play the WAV sound effect (channel -1 means the first free channel)
    Mix_VolumeChunk(sound_effects_map[sound_map_key], MIX_MAX_VOLUME);
    int channel = Mix_PlayChannel(-1, sound_effects_map[sound_map_key], 0); // The third parameter is the loop count (0 means play once)

    if (channel == -1) 
    {
        std::cerr << "[!] Failed to play sound: " << Mix_GetError() << std::endl;
    }

 
}

void SoundManager::PlayMusic(const char* music_key) 
{
    Mix_Music* music = Mix_LoadMUS(music_map[music_key]);
    //std::cout << "[*] Playing the sound effect " << music_map[music_key] << std::endl;
    if (!music) 
    {
        std::cerr << "[!] Failed to load MP3 file: " << Mix_GetError() << std::endl;  
    }

    std::cout << "[*] Playing Music" << music_map[music_key] << std::endl;
    // Check parameters ! Loop, how to pause, switch music ?
    if (-1 == Mix_PlayMusic(music, 1)) 
    {
        std::cerr << "[!] Failed to play music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(music);
        return;
    }
}

void SoundManager::LoadSoundEffect(const char* sound_key, const char* wav_file)
{
    
    // Load a WAV sound effect
    Mix_Chunk* sound_effect = Mix_LoadWAV(wav_file);
    if (!sound_effect)
    {
        std::cerr << "[!] Failed to load WAV file " << wav_file << " : " << Mix_GetError() << std::endl;
        return;
    }

    // Store the loaded sound effect in the map
    sound_effects_map[sound_key] = sound_effect;
}

void SoundManager::FadeOutMusic()
{
 
    
    if (Mix_PlayingMusic()) 
    {
        std::cout << "[*] Fading music out over " << song_fade_time_ms << " milliseconds." << std::endl;
        if (0 == Mix_FadeOutMusic(song_fade_time_ms)) 
        {
            std::cerr << "[!] Failed to fade out music: " << Mix_GetError() << std::endl;
        }
    } else {
        std::cerr << "[!] No music to fade out." << std::endl;
    }
}

