#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include "Player.hpp"
#include <SDL2/SDL_image.h>
#include "Projectiles.hpp"
#include <vector>

class Player;

class Graphics 
{
public:
    // Constructor
    Graphics(const char* title, int width, int height, int pixel_scale);

    // Destructor
    ~Graphics();

    //Hide Window 
    void HideWindow();

    void ShowWindow();

    //Show Window

    // Clean up and quit SDL
    void cleanup();

    void DeactivateWindow();

    SDL_Texture* GetTexture(const char* png_path);

    // Render content
    void render(Player* player, std::vector<Projectile*> &game_projectile);

    SDL_Renderer* GetRenderer();

    int GetScreenHeight();
    int GetScreenWidth();

    void BackgroundUpdate(Uint32 loop);

    

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Background Stuff
    const char* background_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/free-sky-with-clouds-background-pixel-art-set/Clouds/Clouds 5/1.png";
    const char* clouds1_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/free-sky-with-clouds-background-pixel-art-set/Clouds/Clouds 5/3.png";
    SDL_Rect clouds1_src, clouds1_dest;
    int clouds1_animation_index;

    int screen_width;
    int screen_height;
    int pixel_scale;
    
    bool is_shown;

    // Initialize SDL, create window and renderer
    bool init(const char* title, int width, int height);


    // Update game logic
    void update();

    

    
};

#endif