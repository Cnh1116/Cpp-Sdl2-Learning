#include "PrimaryFire.hpp"
#include <iostream>
#include "Sound.hpp"

PrimaryFire::PrimaryFire(int x, int y, float projectile_speed, SDL_Texture* projectile_texture, float projectile_damage, int PIXEL_SCALE)
    : Projectile(x, y, projectile_speed, projectile_texture, projectile_damage, PIXEL_SCALE, true) 
{
}

void PrimaryFire::MoveProjectile() 
{
    dest_rect.y -= speed;
}