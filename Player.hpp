#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <SDL.h>

class Graphics;


class Player
{
    public:
        
        // Constructor
        Player(Graphics* graphics_manager, int PIXEL_SCALE);

        // Actions
        // void FirePrimary();
        bool IsFirePrimaryReady();
        bool IsFireSecondaryReady();
        // void UseShield();

        //UPDATE
        void Update(int x_pos, int y_pos, int SCREEN_WIDTH, int SCREEN_HEIGHT, long loop);

       
        
        // Setters and Getters
        SDL_Rect* GetSrcRect();
        SDL_Rect* GetDstRect();
        
        
        void SetPosition(int x, int y, int SCREEN_WIDTH, int SCREEN_HEIGHT);
        void SetImageScale(int image_scale);
        float GetSpeed();
        void SetSpeed(float speed);

        //Secondary_Fire GetSecondaryFire();
        
        
        
        SDL_Rect* GetSecondaryFirePosition();\
        float GetSecondaryFireSpeed();
        
        // SECON FIRE MARKER
        void SetSecondaryFireMarkerDest();
        
        bool IsSecondaryFireMarkerActive();
        void SetSecondaryFireMarkerActive(bool flag);
        void SetSecondaryFireMarkerPosition();
        SDL_Rect* GetSecondaryFireMarkerCollision();
        SDL_Rect* GetSecondaryFireMarkerPosition();

        float GetBaseDamage();
       

    
    private:
        //STATS
        float player_speed;
        float base_damage;
        
        //IMAGE STUFF
        int BASE_SPRITE_SIZE = 32;
        int image_scale;
        int idle_animation_index;

        SDL_Texture* player_texture;
        SDL_Rect player_source_rect;
        SDL_Rect player_dest_rect;
        
        

        struct Primary_fire
        {
            Uint32 last_fire_time = 0;
            Uint32 cooldown_time_ms = 200; //ms
            // std::string png sprite sheet
            // vector<sdl_rect>
            //const char* .wav effect
        };
        Primary_fire primary_fire;

        struct Secondary_fire
        {
            // MARKER VARIABLES
            bool marker_active;
            SDL_Rect marker_col_rect;
            SDL_Rect marker_dest_rect;
            

            //HUD VARIABLES
            SDL_Rect source_rect;
            SDL_Rect hud_dest_rect;
            
            
            // STATS
            Uint32 last_fire_time = 0;
            Uint32 cooldown_time_ms = 1500; //ms
            float speed = 2.1;
            
            
            // vector<sdl_rect>
            //std::string .wav effect
        };
        Secondary_fire secondary_fire;

        //ITEMS
        //glass_toucans;
        //wooden_owls
        //
};

#endif