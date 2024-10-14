#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SDL2/SDL.h>
#include <vector>

class Graphics;

class Animation
{
    public:
        Animation(Graphics* graphics_manager, const char* sprite_png, Uint32 frame_time_ms, std::vector<SDL_Rect> animation_frames, bool replayable_flag);
        void AdvanceFrame();
        SDL_Rect* GetFrame();
        SDL_Texture* GetTexture();

    private:
            SDL_Texture* animation_texture;
            Uint32 last_frame_time = 0;
            Uint32 cooldown_time_ms; //ms
            int frame_index = 0;
            std::vector<SDL_Rect> frames;
            bool animation_replayable;
};

#endif