#include "SDLWindow.hpp"
#include "sound.hpp"

class Game
{
    public:
        Game();
        void RunGame();
    private:
        SDLWindow* game_window;
        SoundManager* sound_manager;
        
        bool game_over;
};