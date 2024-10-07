#include "Player.hpp"
#include <iostream>
#include "Graphics.hpp"

Player::Player(SDL_Texture* texture, SDL_Texture* secondary_fire_crosshair_texture, int PIXEL_SCALE)
{
    player_dest_rect = {0, 0, BASE_SPRITE_SIZE * PIXEL_SCALE, BASE_SPRITE_SIZE * PIXEL_SCALE};
    player_source_rect = {32, 32, 32, 32}; // IN RENDER, RENDER COPY USES NULL FOR NOW SO THIS IS MAYBE WRONG / DOESNT MATTER UNTIL ANIMATIONS
    player_speed = 3.0;

    player_texture = texture;
    std::cout << "[*] I am a new player";

    secondary_fire = {  {32, 32, 32, 32}, 
                        {player_dest_rect.x, player_dest_rect.y, BASE_SPRITE_SIZE * PIXEL_SCALE, BASE_SPRITE_SIZE * PIXEL_SCALE},  
                        secondary_fire_crosshair_texture};

    
}


bool Player::IsFireSecondaryReady()
{
    Uint32 current_time = SDL_GetTicks();

    if ( (current_time - last_secondary_fire_time) >= secondary_fire_cdr )
    {
        std::cout << "[*] SECONDARY FIRING !\n";
        last_secondary_fire_time = current_time;
        return(true);
    }

    else
    {
        std::cout << "[*] Secondary Fire on cooldown\n";
        return(false);
    }
}

bool Player::IsFirePrimaryReady()
{
    Uint32 current_time = SDL_GetTicks();

    if ( (current_time - last_primary_fire_time) >= primary_fire_cdr )
    {
        std::cout << "[*] PRIMARY FIRING !\n";
        last_primary_fire_time = current_time;
        return(true);
    }

    else
    {
        std::cout << "[*] Primary Fire on cooldown\n";
        return(false);
    }
}

void Player::SetImageScale(int image_scale)
{
    player_dest_rect.w = BASE_SPRITE_SIZE * image_scale;
    player_dest_rect.h = BASE_SPRITE_SIZE * image_scale;
}

void Player::SetPosition(int x, int y, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // Update position with boundary checks.
    if (player_dest_rect.x + x >= 0 && player_dest_rect.x + x <= SCREEN_WIDTH - player_dest_rect.w) 
    {
        player_dest_rect.x += x ;  // Move along x-axis within bounds
        secondary_fire.secondary_fire_dest_rect.x = player_dest_rect.x;
    }
    if (player_dest_rect.y + y >= 0 && player_dest_rect.y + y <= SCREEN_HEIGHT - player_dest_rect.h) 
    {
        player_dest_rect.y += y ;  // Move along y-axis within bounds
        secondary_fire.secondary_fire_dest_rect.y = player_dest_rect.y - 256;
    }

}

// Getters and Setters:
SDL_Texture* Player::GetTexture()  
{
    return player_texture;
}

void Player::SetTexture(SDL_Texture* texture)
{
    player_texture = texture;
}

SDL_Rect* Player::GetSrcRect()  
{
    return &player_source_rect;
}

SDL_Rect* Player::GetDstRect()  
{
    return &player_dest_rect;
}

int Player::GetSpeed()
{
    return player_speed;
}

void Player::SetSpeed(float speed)
{
    player_speed = speed;
}

SDL_Texture* Player::GetSecondaryFireTexture()
{
    return secondary_fire.secondary_fire_crosshair;
}

SDL_Rect* Player::GetSecondaryFirePosition()
{
    return &secondary_fire.secondary_fire_dest_rect;
}

float Player::GetBaseDamage()
{
    return(base_damage);
}