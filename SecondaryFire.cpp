#include "SecondaryFire.hpp"
#include <iostream>

SecondaryFire::SecondaryFire(int x, int y, float projectile_speed, SDL_Texture* projectile_texture, int PIXEL_SCALE)
    : Projectile(x, y, projectile_speed, projectile_texture, 0.0f, PIXEL_SCALE, true) 
{
}

void SecondaryFire::MoveProjectile() 
{
    dest_rect.y -= speed;
}