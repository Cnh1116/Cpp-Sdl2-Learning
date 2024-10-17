#include <iostream>
#include "Projectiles.hpp"
#include "Graphics.hpp"

Projectile::Projectile(int x, int y, float projectile_speed, float projectile_damage, int PIXEL_SCALE, bool player_projectile_flag, std::string main_texture_key_str, std::vector<SDL_Rect> frames, std::string impact_texture_key_str, std::vector<SDL_Rect> imp_frames, Uint32 frame_cooldown_ms, bool replayable)
    : dest_rect({x, y,  32 * PIXEL_SCALE , 32 * PIXEL_SCALE }),
    speed(projectile_speed),
    damage(projectile_damage),
    player_projectile(player_projectile_flag),
    main_texture_key(main_texture_key_str),
    impact_texture_key(impact_texture_key_str),
    current_frame_index(0),
    main_frames(frames),
    impact_frames(imp_frames),
    frame_time_ms(frame_cooldown_ms),
    last_frame_time(0),
    animation_replayable(replayable),
    state("main"),
    pixel_scale(PIXEL_SCALE),
    collision_rect(dest_rect)

{
}

std::string Projectile::GetTextureKey()
{
    
    if (state == "main")
        return main_texture_key;
    else if (state == "impact")
        return impact_texture_key;
}

Projectile::~Projectile()
{
}

void Projectile::MoveProjectile()
{

    dest_rect.y += speed;

}

void Projectile::UpdateState(const char* state_str)
{
    state = state_str; //EVENTUALY THIS SHOULD BE A STRING CALLED ANIMATION STATE
    last_frame_time = 0;
    current_frame_index = 0;
}

const char* Projectile::GetState()
{
    return state;
}

void Projectile::Update()
{
    MoveProjectile();
    
    if (state == "impact")
    {
        speed = -1;
    }
    if (state == "impact" && current_frame_index >= impact_frames.size() - 1)
    {
        state = "delete";
    }
}

SDL_Rect* Projectile::GetDstRect()
{
    return(&dest_rect);
}

SDL_Rect* Projectile::GetFrame()
{
    if (state == "main")
        return &main_frames[current_frame_index];
    else if (state == "impact")
        return &impact_frames[current_frame_index];
}

Uint32 Projectile::GetFrameTime()
{
    return frame_time_ms;
}
Uint32 Projectile::GetLastFrameStart()
{
    return last_frame_time;
}

bool Projectile::IsReplayable()
{
    return animation_replayable;
}

int Projectile::NumOfFrames()
{
    // EVENTUALLY RETURN std::map<const char*, std::vector<SDL_Rect>> Have a map of textures so diff animations are possible on proj, enemies, and player
    if (state == "main")
        return main_frames.size();
    else if (state == "impact")
        return impact_frames.size();
}

SDL_Rect* Projectile::GetCollisionRect()
{
    return &collision_rect;
}

void Projectile::AdvanceFrame()
{
    current_frame_index++;
}

// PRIMARY FIRE

PrimaryFire::PrimaryFire(int x, int y, float projectile_speed, float projectile_damage, int PIXEL_SCALE)
    : Projectile(x, y, projectile_speed, projectile_damage, PIXEL_SCALE, true, "primary_fire", { {0,0,32,32}, {32,0,32,32}, {64,0,32,32}, {96,0,32,32} }, "primary_fire_impact", { {0,0,32,32} }, 60, true)
{
}

void PrimaryFire::MoveProjectile() 
{
    dest_rect.y -= speed;
}

// SECONDARY FIRE
SecondaryFire::SecondaryFire(int x, int y, float projectile_speed, int PIXEL_SCALE)
    : Projectile(x, y, projectile_speed, 0.0f, PIXEL_SCALE, true, "secondary_fire", { {0,0,32,32}, {32,0,32,32}, {64,0,32,32}, {96,0,32,32}, {128,0,32,32} }, "secondary_fire_impact", { {0,0,32,32}, {32,0,32,32}, {64,0,32,32}, {96,0,32,32}, {128,0,32,32} }, 200, false)
{
}

void SecondaryFire::MoveProjectile() 
{
    dest_rect.y -= speed;
    collision_rect = { (dest_rect.x + dest_rect.w / 2),  (dest_rect.y + dest_rect.h / 2), 128, 128 };
}