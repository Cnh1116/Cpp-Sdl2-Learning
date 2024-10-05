#include "Player.hpp"
#include <iostream>
#include "SDLWindow.hpp"

Player::Player(SDL_Texture* texture)
{
    dest_rect = {0,0,32,32};
    source_rect = {32, 32, 32, 32};
    speed = 2.0;
    player_texture = texture;
    std::cout << "[*] I am a new player";
    
}

SDL_Texture* Player::GetTexture()  
{
    return player_texture;
}

SDL_Rect* Player::GetSrcRect()  
{
    return &source_rect;
}

SDL_Rect* Player::GetDstRect()  
{
    return &dest_rect;
}

void Player::SetTexture(SDL_Texture* texture)
{
    player_texture = texture;
}

void Player::SetImageScale(int image_scale)
{
    dest_rect.w = BASE_SPRITE_SIZE * image_scale;
    dest_rect.h = BASE_SPRITE_SIZE * image_scale;
}

void Player::SetPosition(int x, int y)
{
    
    
   
   // Update position with boundary checks. Width is times pixel scale
    if (dest_rect.x + x >= 0 && dest_rect.x + x <= 800 - dest_rect.w * 4) {
        dest_rect.x += x ;  // Move along x-axis within bounds
    }
    if (dest_rect.y + y >= 0 && dest_rect.y + y <= 800 - dest_rect.h * 4) {
        dest_rect.y += y ;  // Move along y-axis within bounds
    }
}
