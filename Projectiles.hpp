
#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include <SDL2/SDL.h>



class Projectile
{
    public:
        Projectile(int x, int y, float projectile_speed, SDL_Texture* projectile_texture, float projectile_damage, int PIXEL_SCALE, bool player_projectile_flag);
        virtual void MoveProjectile() = 0;
        SDL_Texture* GetTexture();
        SDL_Rect* GetDstRect();

        SDL_Rect dest_rect;
        SDL_Rect src_rect;
        float speed;
        float damage;
        SDL_Texture* texture;
        int BASE_SPRITE_SIZE = 32;
        int PIXEL_SCALE;
        bool player_projectile;

    private:
        
};

#endif

