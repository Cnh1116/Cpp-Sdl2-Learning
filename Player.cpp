#include "Player.hpp"
#include <iostream>
#include "Graphics.hpp"

Player::Player(Graphics* graphics_manager, int PIXEL_SCALE)
{
    
    std::cout << "[*] I am a new player";
    image_scale = PIXEL_SCALE;
    player_dest_rect = {0, 0, BASE_SPRITE_SIZE * image_scale, BASE_SPRITE_SIZE * image_scale};
    player_source_rect = {32, 32, 32, 32}; // IN RENDER, RENDER COPY USES NULL FOR NOW SO THIS IS MAYBE WRONG / DOESNT MATTER UNTIL ANIMATIONS
    player_speed = 5.0;

    player_texture = graphics_manager->GetTexture(player_sprite_png);
   
    
    secondary_fire.source_rect = {32, 32, 32, 32}; 
    secondary_fire.hud_dest_rect  = {player_dest_rect.x, player_dest_rect.y, BASE_SPRITE_SIZE * image_scale, BASE_SPRITE_SIZE * image_scale};
    secondary_fire.crosshair = graphics_manager->GetTexture(secondary_fire.hud_png);
    secondary_fire.marker = graphics_manager->GetTexture(secondary_fire.marker_png);
    secondary_fire.marker_active = false;

}


void Player::Update(int x_pos, int y_pos, int SCREEN_WIDTH, int SCREEN_HEIGHT, u_long loop)
{
    SetPosition(x_pos, y_pos, SCREEN_WIDTH, SCREEN_HEIGHT);
    // Set animatino state.
    //if  idle_animation_index == idle_animation vector.size(), idle_animation_index == 0; else idle_animation_index ++
}

void Player::SetSecondaryFireMarkerActive(bool flag)
{
    secondary_fire.marker_active = flag;
}

bool Player::IsSecondaryFireMarkerActive()
{
    return secondary_fire.marker_active;
}

bool Player::IsFireSecondaryReady()
{
    Uint32 current_time = SDL_GetTicks();

    if ( (current_time - secondary_fire.last_fire_time) >= secondary_fire.cooldown_time_ms )
    {
        std::cout << "[*] SECONDARY FIRING !\n";
        secondary_fire.last_fire_time = current_time;
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

    if ( (current_time - primary_fire.last_fire_time) >= primary_fire.cooldown_time_ms )
    {
        std::cout << "[*] PRIMARY FIRING !\n";
        primary_fire.last_fire_time = current_time;
        return(true);
    }

    else
    {
        std::cout << "[*] Primary Fire on cooldown\n";
        return(false);
    }
}

void Player::SetImageScale(int scale)
{
   image_scale = scale;
}

void Player::SetPosition(int x, int y, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // Update position with boundary checks.
    if (player_dest_rect.x + x >= 0 && player_dest_rect.x + x <= SCREEN_WIDTH - player_dest_rect.w) 
    {
        player_dest_rect.x += x ;  // Move along x-axis within bounds
        secondary_fire.hud_dest_rect.x = player_dest_rect.x;
    }
    if (player_dest_rect.y + y >= 0 && player_dest_rect.y + y <= SCREEN_HEIGHT - player_dest_rect.h) 
    {
        player_dest_rect.y += y ;  // Move along y-axis within bounds
        secondary_fire.hud_dest_rect.y = player_dest_rect.y - (256 + 64);
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
    return secondary_fire.crosshair;
}

SDL_Texture* Player::GetSecondaryFireMarkerTexture()
{
    return secondary_fire.marker;
}

SDL_Rect* Player::GetSecondaryFirePosition()
{
    return &secondary_fire.hud_dest_rect;
}

float Player::GetSecondaryFireSpeed()
{
    return secondary_fire.speed;
}

void Player::SetSecondaryFireMarkerPosition()
{
    secondary_fire.marker_dest_rect = {secondary_fire.hud_dest_rect.x, secondary_fire.hud_dest_rect.y, BASE_SPRITE_SIZE * image_scale, BASE_SPRITE_SIZE * image_scale};
    secondary_fire.marker_col_rect = {secondary_fire.hud_dest_rect.x, secondary_fire.hud_dest_rect.y, BASE_SPRITE_SIZE, BASE_SPRITE_SIZE};
}

SDL_Rect* Player::GetSecondaryFireMarkerCollision()
{
    return &secondary_fire.marker_col_rect;
}

SDL_Rect* Player::GetSecondaryFireMarkerPosition()
{
    return &secondary_fire.marker_dest_rect;
}

float Player::GetBaseDamage()
{
    return(base_damage);
}