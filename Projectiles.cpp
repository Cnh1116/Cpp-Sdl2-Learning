#include "Projectiles.hpp"
#include "Graphics.hpp"

Projectile::Projectile(int x, int y, float projectile_speed, Graphics* graphics_manager, float projectile_damage, int PIXEL_SCALE, bool player_projectile_flag)
    : dest_rect({x, y,  32*4, 32*4}),
    speed(projectile_speed),
    damage(projectile_damage),
    player_projectile(player_projectile_flag)
{
}

void Projectile::MoveProjectile()
{
    dest_rect.y =+ speed;
}

SDL_Texture* Projectile::GetTexture() 
{
    return(texture);
}
SDL_Rect* Projectile::GetDstRect()
{
    return(&dest_rect);
}

PrimaryFire::PrimaryFire(int x, int y, float projectile_speed, Graphics* graphics_manager, float projectile_damage, int PIXEL_SCALE)
    : Projectile(x, y, projectile_speed, graphics_manager, projectile_damage, PIXEL_SCALE, true) 
{
    texture = graphics_manager->GetTexture(projectile_png);
}

void PrimaryFire::MoveProjectile() 
{
    dest_rect.y -= speed;
}

SecondaryFire::SecondaryFire(int x, int y, float projectile_speed, Graphics* graphics_manager, int PIXEL_SCALE)
    : Projectile(x, y, projectile_speed, graphics_manager, 0.0f, PIXEL_SCALE, true) 
{
    texture = graphics_manager->GetTexture(projectile_png);
}

void SecondaryFire::MoveProjectile() 
{
    dest_rect.y -= speed;
}