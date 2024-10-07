#ifndef PRIMARY_HPP
#define PRIMARY_HPP

#include <SDL2/SDL.h>
#include "Projectiles.hpp"

class PrimaryFire : public Projectile {
public:
    PrimaryFire(int x, int y, float projectile_speed, SDL_Texture* projectile_texture, float projectile_damage, int PIXEL_SCALE);
    void MoveProjectile() override;
};


#endif

