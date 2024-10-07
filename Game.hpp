#include "Graphics.hpp"
#include "Sound.hpp"
#include <vector>
#include "Projectiles.hpp"
#include "SecondaryFire.hpp"
#include "PrimaryFire.hpp"

class Projectile;



class Game
{
    public:
        Game();
        void RunGame();
        void HandleKeyInput(SDL_Event event, Player* player, std::vector<Projectile*> &game_projectile);
    
    private:
        Graphics* graphics_manager;
        SoundManager* sound_manager;
        // player
        // enemy spawner
        // item spawner
        bool game_over;
        Player player;

        int times_X_pressed;
};

