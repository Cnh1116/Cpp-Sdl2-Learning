
#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include <SDL2/SDL.h>

class Graphics;

class Projectile
{
    public:
        Projectile(int x, int y, float projectile_speed, Graphics* graphics_manager, float projectile_damage, int PIXEL_SCALE, bool player_projectile_flag);
        virtual void MoveProjectile() = 0;
        SDL_Texture* GetTexture();
        SDL_Rect* GetDstRect();

        SDL_Rect dest_rect;
        SDL_Rect src_rect;
        float speed;
        float damage;
        SDL_Texture* texture;
        const char* projectile_png;
        int BASE_SPRITE_SIZE = 32;
        int PIXEL_SCALE;
        bool player_projectile;

    private:
        
};

class PrimaryFire : public Projectile {
public:
    PrimaryFire(int x, int y, float projectile_speed, Graphics* graphics_manager, float projectile_damage, int PIXEL_SCALE);
    void MoveProjectile() override;
    const char* projectile_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sprites/projectile-sprites/primary_fire.png";
};

class SecondaryFire : public Projectile {
public:
    SecondaryFire(int x, int y, float projectile_speed, Graphics* graphics_manager, int PIXEL_SCALE);
    void MoveProjectile() override;
    const char* projectile_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sprites/projectile-sprites/secondary_fire_projectile.png";
    
    
    //void UPDATE(): Calls moveprojectile function and increments the frame to play of an animation
};

#endif

