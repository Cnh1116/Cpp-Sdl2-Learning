#include "sound.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

SoundManager::SoundManager()
{
    std::cout << "[*] Initializing Audio.";
    if (0 != SDL_Init(SDL_INIT_AUDIO))
    {
        std::cout << "[!] SDL_Init Audio did not return 0 code." << SDL_GetError() << std::endl;
        exit(1);
    }

    if(0 > Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
    {
        std::cout << "[!] Mix_OpenAudio did not return 0 code." << Mix_GetError() << std::endl;
        exit(1);
    }
}

SoundManager::~SoundManager()
{
    std::cout << "[*] Turning off the SDL Audio.";
    Mix_CloseAudio();
}


void SoundManager::PlaySound(const char* wav_file_path)
{
    // Load a WAV sound effect
    Mix_Chunk* soundEffect = Mix_LoadWAV(wav_file_path);
    if (!soundEffect) 
    {
        std::cerr << "[!] Failed to load WAV file: " << Mix_GetError() << std::endl;
    }

    std::cout << "[*] Playing Sound Effect" << wav_file_path << std::endl;
    // Play the WAV sound effect (channel -1 means the first free channel)
    Mix_VolumeChunk(soundEffect, MIX_MAX_VOLUME);
    Mix_PlayChannel(-1, soundEffect, 0); // The third parameter is the loop count (0 means play once)

      // Clean up loaded sound and music
    Mix_FreeChunk(soundEffect);


    
}

void SoundManager::PlayMusic(const char* mp3_file_path) 
{
    Mix_Music* music = Mix_LoadMUS(mp3_file_path);
    if (!music) 
    {
        std::cerr << "[!] Failed to load MP3 file: " << Mix_GetError() << std::endl;
        
    }

    std::cout << "[*] Playing Music" << mp3_file_path << std::endl;
    // Play the MP3 music file (the second parameter is the loop count, -1 means infinite loop)
    Mix_PlayMusic(music, 1);  // Play the music once (1 loop)

    Mix_FreeMusic(music);

}


