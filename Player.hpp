#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <SDL2/SDL.h>


class Player
{
    public:
        
        Player(SDL_Texture* player_texture);
        SDL_Rect* GetSrcRect();
        SDL_Rect* GetDstRect();
        SDL_Texture* GetTexture();

        void SetTexture(SDL_Texture* texture);
        void SetPosition(int x, int y);
        void SetImageScale(int image_scale);
       

    
    private:
        SDL_Texture* player_texture;
        SDL_Rect source_rect;
        SDL_Rect dest_rect;
        float speed;
        int BASE_SPRITE_SIZE = 32;
};

#endif