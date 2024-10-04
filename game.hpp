#include "SDLWindow.hpp"
#include "sound.hpp"

class Game
{
    public:
        Game();
        void RunGame();
        void HandleKeyInput(SDL_Event event);
    
    private:
        SDLWindow* game_window;
        SoundManager* sound_manager;
        // player
        // enemy spawner
        // item spawner
        bool game_over;

        int times_X_pressed;
};