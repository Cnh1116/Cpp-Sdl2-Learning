#include <iostream>

class SoundManager
{
    public:
        SoundManager(); //Maybe give directory where sounds are ??
        ~SoundManager();
        void PlaySound(const char* wav_file_path);
        void PlayMusic(const char* mp3_file_path);

    private:
};