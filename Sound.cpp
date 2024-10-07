#include "Sound.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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
        std::cout << "[!] Mix_OpenAudio did not return 0 code.\n" << Mix_GetError() << std::endl;
        exit(1);
    }
}

SoundManager::~SoundManager()
{
    std::cout << "[*] Turning off the SDL Audio.\n";
    Mix_CloseAudio();
}


void SoundManager::PlaySound(const char* wav_file_path)
{
    if (1 == Mix_Playing(-1))
    {
        std::cout << "[*] A sound is already playing, doing nothing.";
        return;
    }
    
    // Load a WAV sound effect
    Mix_Chunk* soundEffect = Mix_LoadWAV(wav_file_path);
    if (!soundEffect) 
    {
        std::cerr << "[!] Failed to load WAV file: " << Mix_GetError() << std::endl;
    }

    std::cout << "[*] Playing Sound Effect" << wav_file_path << std::endl;
    // Play the WAV sound effect (channel -1 means the first free channel)
    Mix_VolumeChunk(soundEffect, MIX_MAX_VOLUME);
    int channel = Mix_PlayChannel(-1, soundEffect, 0); // The third parameter is the loop count (0 means play once)

    if (channel == -1) 
    {
        std::cerr << "[!] Failed to play sound: " << Mix_GetError() << std::endl;
        Mix_FreeChunk(soundEffect);
        Mix_FreeChunk(soundEffect);
    }


    
}

void SoundManager::PlayMusic(const char* mp3_file_path) 
{
    Mix_Music* music = Mix_LoadMUS(mp3_file_path);
    if (!music) 
    {
        std::cerr << "[!] Failed to load MP3 file: " << Mix_GetError() << std::endl;  
    }

    std::cout << "[*] Playing Music" << mp3_file_path << std::endl;
    // Check parameters ! Loop, how to pause, switch music ?
    if (-1 == Mix_PlayMusic(music, 1)) 
    {
        std::cerr << "[!] Failed to play music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(music);
        return;
    }
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

