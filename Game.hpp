#include "Graphics.hpp"
#include "Sound.hpp"
#include <vector>
#include "Projectiles.hpp"
#include "Player.hpp"

class Projectile;



class Game
{
    public:
        Game();
        void RunGame();
        void HandleKeyInput(SDL_Event event, Player* player, std::vector<Projectile*> &game_projectile);
        void FPSLogic(Uint32 current_tick);

        // Collision Functions
        void HandleCollisions(Player* player, std::vector<Projectile*> &game_projectiles);
        bool RectRectCollision(SDL_Rect* rect_1, SDL_Rect* rect_2);
        bool RectCircleCollision(SDL_Rect* rect_1, int circle_x, int circle_y, int circle_r);
        bool CircleCircleCollision(int circle1_x, int circle1_y, int circle1_r, int circle2_x, int circle2_y, int circle2_r);

    
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

