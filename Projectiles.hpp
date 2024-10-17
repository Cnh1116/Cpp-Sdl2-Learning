
#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include <SDL.h>

#include <iostream>
#include <vector>
//#include "Animation.hpp"

class Graphics;


class Projectile
{
    public:
        // Constructors
        Projectile(int x, int y, float projectile_speed, float projectile_damage, int PIXEL_SCALE, bool player_projectile_flag, 
            std::string main_texture_key, std::vector<SDL_Rect> main_frames, std::string impact_texture_key, std::vector<SDL_Rect> impact_frames, Uint32 frame_cooldown_ms, bool animation_replayable);
        ~Projectile();

        // Setters and Getters
        SDL_Rect* GetDstRect();
        std::string GetTextureKey();
        Uint32 GetFrameTime();
        Uint32 GetLastFrameStart();
        SDL_Rect* GetFrame();
        bool IsReplayable();
        int NumOfFrames();
        const char* GetState();
        SDL_Rect* GetCollisionRect();

        //Other Functions
        void AdvanceFrame();
        void UpdateState(const char* state);
        void Update(); //Method to move projectile every frame, and do logic depending on state
        
        // Override Functions
        virtual void MoveProjectile() = 0;
        

        // Stats   
        float speed;
        float damage;

        // Other vars
        const char* state;

        // Texture Stuff
        std::vector<SDL_Rect> main_frames;
        std::vector<SDL_Rect> impact_frames;
        std::string main_texture_key;
        std::string impact_texture_key;
        int current_frame_index;
        SDL_Rect dest_rect;
        SDL_Rect collision_rect;
        Uint32 frame_time_ms;
        Uint32 last_frame_time;
        
        int BASE_SPRITE_SIZE = 32;
        int pixel_scale;
        bool player_projectile;
        bool animation_replayable;

    private:
        //Animation main_animation;
        
};

class PrimaryFire : public Projectile {
public:
    PrimaryFire(int x, int y, float projectile_speed, float projectile_damage, int PIXEL_SCALE);
    void MoveProjectile() override;
};

class SecondaryFire : public Projectile {
public:
    SecondaryFire(int x, int y, float projectile_speed, int PIXEL_SCALE);
    void MoveProjectile() override;
    
    
    //void UPDATE(): Calls moveprojectile function and increments the frame to play of an animation
};

#endif

