#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <SDL2/SDL.h>

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
        void Update(int x_pos, int y_pos, int SCREEN_WIDTH, int SCREEN_HEIGHT, u_long loop);

       
        
        // Setters and Getters
        SDL_Rect* GetSrcRect();
        SDL_Rect* GetDstRect();
        SDL_Texture* GetTexture();
        void SetTexture(SDL_Texture* texture);
        void SetPosition(int x, int y, int SCREEN_WIDTH, int SCREEN_HEIGHT);
        void SetImageScale(int image_scale);
        int GetSpeed();
        void SetSpeed(float speed);

        //Secondary_Fire GetSecondaryFire();
        
        SDL_Texture* GetSecondaryFireTexture();
        
        SDL_Rect* GetSecondaryFirePosition();\
        float GetSecondaryFireSpeed();
        
        // SECON FIRE MARKER
        void SetSecondaryFireMarkerDest();
        SDL_Texture* GetSecondaryFireMarkerTexture();
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
        const char* player_sprite_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sprites/player-sprites/player.png";
        int idle_animation_index;

        SDL_Texture* player_texture;
        SDL_Rect player_source_rect;
        SDL_Rect player_dest_rect;
        
        

        struct Primary_fire
        {
            Uint32 last_fire_time = 0;
            Uint32 cooldown_time_ms = 120; //ms
            // const char* png sprite sheet
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
            SDL_Texture* marker;
            const char* marker_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sprites/player-sprites/secondary_fire_marker.png";

            //HUD VARIABLES
            SDL_Rect source_rect;
            SDL_Rect hud_dest_rect;
            SDL_Texture* crosshair;
            const char* hud_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sprites/player-sprites/secondary_fire_hud.png";
            
            // STATS
            Uint32 last_fire_time = 0;
            Uint32 cooldown_time_ms = 1500; //ms
            float speed = 4.5;
            
            
            // vector<sdl_rect>
            //const char* .wav effect
        };
        Secondary_fire secondary_fire;

        //ITEMS
        //glass_toucans;
        //wooden_owls
        //
};

#endif