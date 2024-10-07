#include "Projectiles.hpp"

Projectile::Projectile(int x, int y, float projectile_speed, SDL_Texture* projectile_texture, float projectile_damage, int PIXEL_SCALE, bool player_projectile_flag)
    : dest_rect({x, y,  32*4, 32*4}),
    speed(projectile_speed),
    texture(projectile_texture),
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