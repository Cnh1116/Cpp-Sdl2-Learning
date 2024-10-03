#include "SDLWindow.hpp"

class Game
{
    public:
        Game();
        void RunGame();
    private:
        SDLWindow* game_window;
        SDLWindow* debug_window;
};