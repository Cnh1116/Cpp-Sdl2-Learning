#include "Animation.hpp"
#include "Graphics.hpp"
#include <iostream>

Animation::Animation(Graphics* graphics_manager, const char* sprite_png, Uint32 frame_time_ms, std::vector<SDL_Rect> animation_frames, bool replayable_flag)
{
            std::cout << "[*] Inside of animation constructor\n";
            animation_texture = graphics_manager->GetTexture("sprite_png");
            cooldown_time_ms = frame_time_ms;
            frames = animation_frames;
            animation_replayable = replayable_flag;
}

void Animation::AdvanceFrame()
{
    Uint32 current_time = SDL_GetTicks();

    if ( (current_time - last_frame_time) >= cooldown_time_ms) //WE CAN INCREMENT FRAME
    {
        if (frame_index >= frames.size() && !animation_replayable)
       {
            return;
       }

        frame_index++;
        if (frame_index >= frames.size())
        {
            frame_index = 0;
        }
              
    }

}

SDL_Rect* Animation::GetFrame()
{
    return &frames.at(frame_index);
}

SDL_Texture* Animation::GetTexture()
{
    return animation_texture;
}


            