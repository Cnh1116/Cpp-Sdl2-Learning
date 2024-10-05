#include <iostream>

class SoundManager
{
    public:
        SoundManager(); //Maybe give directory where sounds are ??
        ~SoundManager();
        void PlaySound(const char* wav_file_path);
        void PlayMusic(const char* mp3_file_path);
        void FadeOutMusic();

        const char* sound_1 = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sounds/mixkit-glass-hitting-a-metal-2183.wav";
        const char* song_1 = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/music/ChrisChristodoulou-TheyMightAsWellBeDeadROR2_SurvivorsoftheVoid(2022).mp3";

        

    private:
        int song_fade_time_ms = 1000;
        
};