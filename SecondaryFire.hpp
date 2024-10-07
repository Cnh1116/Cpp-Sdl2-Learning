#ifndef SECONDARY_HPP
#define SECONDARY_HPP

#include <SDL2/SDL.h>
#include "Projectiles.hpp"

class SecondaryFire : public Projectile {
public:
    SecondaryFire(int x, int y, float projectile_speed, SDL_Texture* projectile_texture, int PIXEL_SCALE);
    void MoveProjectile() override;
};


#endif

