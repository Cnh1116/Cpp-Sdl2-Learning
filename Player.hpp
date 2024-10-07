#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <SDL2/SDL.h>


class Player
{
    public:
        
        // Constructor
        Player(SDL_Texture* player_texture, SDL_Texture* secondary_fire_crosshair, int PIXREL_SCALE);

        // Actions
        // void FirePrimary();
        bool IsFirePrimaryReady();
        bool IsFireSecondaryReady();
        
        // void UseShield();

        
        // Setters and Getters
        SDL_Rect* GetSrcRect();
        SDL_Rect* GetDstRect();
        SDL_Texture* GetTexture();
        void SetTexture(SDL_Texture* texture);
        void SetPosition(int x, int y, int SCREEN_WIDTH, int SCREEN_HEIGHT);
        void SetImageScale(int image_scale);
        int GetSpeed();
        void SetSpeed(float speed);
        SDL_Texture* GetSecondaryFireTexture();
        SDL_Rect* GetSecondaryFirePosition();\
        float GetBaseDamage();
       

    
    private:
        SDL_Texture* player_texture;
        SDL_Rect player_source_rect;
        SDL_Rect player_dest_rect;
        float player_speed;
        float base_damage;
        int BASE_SPRITE_SIZE = 32;
        
        Uint32 last_secondary_fire_time = 0;
        Uint32 last_primary_fire_time = 0;
        Uint32 secondary_fire_cdr = 1000; //ms
        Uint32 primary_fire_cdr = 120; //ms

        struct Secondary_fire
        {
            SDL_Rect secondary_fire_source_rect;
            SDL_Rect secondary_fire_dest_rect;
            SDL_Texture* secondary_fire_crosshair;
        };

        Secondary_fire secondary_fire;
};

#endif