#include "SDLWindow.hpp"
#include "sound.hpp"


class Game
{
    public:
        Game();
        void RunGame();
        void HandleKeyInput(SDL_Event event, Player* player);
    
    private:
        SDLWindow* game_window;
        SoundManager* sound_manager;
        // player
        // enemy spawner
        // item spawner
        bool game_over;
        Player player;

        int times_X_pressed;
};