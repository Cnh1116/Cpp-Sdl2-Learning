#include "SDLWindow.hpp"
#include <iostream>

// Constructor
SDLWindow::SDLWindow(const char* title, int width, int height, int scale)
    : window(nullptr), renderer(nullptr), is_shown(false) 
{
    
    screen_width = width;
    screen_height = height;
    pixel_scale = scale;
    
    if (init(title, width, height)) 
    {
        is_shown = true;
    }
}

// Destructor
SDLWindow::~SDLWindow() 
{
    cleanup();
}

void SDLWindow::HideWindow()
{
    std::cout << "[*] HideWindow() Called";
    is_shown = false;
    SDL_HideWindow(window);  
}

void SDLWindow::ShowWindow()
{
    std::cout << "[*] ShowWindow() Called";
    is_shown = true;
    SDL_ShowWindow(window);
}

void SDLWindow::DeactivateWindow()
{
    is_shown = false;
}

// Initialize SDL, create window and renderer
bool SDLWindow::init(const char* title, int width, int height) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        std::cerr << "[!] SDL Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
    if (!window) 
    {
        std::cerr << "[!] Window creation error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) 
    {
        std::cerr << "[!] Renderer creation error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}


SDL_Texture* SDLWindow::GetTexture(const char* png_path)
{
    SDL_Surface* temp_surface = IMG_Load(png_path);
    SDL_Texture* retreived_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    if (NULL == retreived_texture)
    {
        std::cout << "[!] Failed to load player's texture.";
        exit(1);
    }
    SDL_FreeSurface(temp_surface);

    return retreived_texture;
}

// Render content
void SDLWindow::render(Player* player) {
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    if (NULL == player->GetDstRect())
    {
        std::cerr << "[!] DstRect for the player is NULL.";
    }


    // Render Background

    // Render Player
    int x = player->GetDstRect()->x;
    int y = player->GetDstRect()->y;
    int w = player->GetDstRect()->w * pixel_scale;
    int h = player->GetDstRect()->h * pixel_scale;

    if ( 0 != SDL_RenderCopy(renderer, player->GetTexture(), NULL, new SDL_Rect {x, y, w, h}))
    {
        std::cout << "[!] Player failed to render.\n";
    }
    // Render Enemies from enemy vector
    // Render Items from item vector
    // Render Projectiles from Projectile Vector ?

    SDL_RenderPresent(renderer);
}

int SDLWindow::GetScreenWidth()
{
    return screen_width;
}

int SDLWindow::GetScreenHeight()
{
    return screen_height;
}

SDL_Renderer* SDLWindow::GetRenderer()
{
    return renderer;
}

// Clean up and quit SDL
void SDLWindow::cleanup() 
{
    std::cout << "[*] Cleaning up window.\n";

    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window) { SDL_DestroyWindow(window); }
}