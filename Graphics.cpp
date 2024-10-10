#include "Graphics.hpp"
#include <iostream>
#include <vector>
#include "Projectiles.hpp"

// Constructor
Graphics::Graphics(const char* title, int width, int height, int scale)
    : window(nullptr), renderer(nullptr), is_shown(false) , clouds1_animation_index(0)
{
    
    screen_width = width;
    screen_height = height;
    pixel_scale = scale;
    clouds1_dest = {0, 0, 576, 324};
    
    if (init(title, width, height)) 
    {
        is_shown = true;
    }
}

// Destructor
Graphics::~Graphics() 
{
    cleanup();
}

void Graphics::HideWindow()
{
    std::cout << "[*] HideWindow() Called";
    is_shown = false;
    SDL_HideWindow(window);  
}

void Graphics::ShowWindow()
{
    std::cout << "[*] ShowWindow() Called";
    is_shown = true;
    SDL_ShowWindow(window);
}

void Graphics::DeactivateWindow()
{
    is_shown = false;
}

// Initialize SDL, create window and renderer
bool Graphics::init(const char* title, int width, int height) 
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


SDL_Texture* Graphics::GetTexture(const char* png_path)
{
    SDL_Surface* temp_surface = IMG_Load(png_path);
    SDL_Texture* retreived_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    if (NULL == retreived_texture)
    {
        std::cout << "[!] Failed to load texture" << png_path << std::endl;;
        exit(1);
    }
    SDL_FreeSurface(temp_surface);

    return retreived_texture;
}

// Render content
void Graphics::render(Player* player, std::vector<Projectile*> &game_projectiles) {
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    if (NULL == player->GetDstRect())
    {
        std::cerr << "[!] DstRect for the player is NULL.";
    }


    // Render Background
    if ( 0 != SDL_RenderCopy(renderer, GetTexture(background_png), NULL, NULL) ) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Background failed to render.\n";
    }

    // Render Background Clouds
    if ( 0 != SDL_RenderCopy(renderer, GetTexture(clouds1_png), NULL, &clouds1_dest) ) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Background failed to render.\n";
    }

    
    // Render Enemies from enemy vector

    // Render Items from item vector

    // For Projectile in game_projectiles list, if their dest rect is withing the bounds of the screen, render it
    for (int i = 0; i < game_projectiles.size(); i++)
    {  
        // Update position with boundary checks.
        if (game_projectiles.at(i)->GetDstRect()->x >= 0 && 
        game_projectiles.at(i)->GetDstRect()->x  <= screen_width - game_projectiles.at(i)->GetDstRect()->w &&
        game_projectiles.at(i)->GetDstRect()->y + game_projectiles.at(i)->GetDstRect()->h >= 0 && 
        game_projectiles.at(i)->GetDstRect()->y  <= screen_height) 
        {
            if ( 0 != SDL_RenderCopy(renderer, game_projectiles.at(i)->GetTexture(), NULL, game_projectiles.at(i)->GetDstRect())) //Second arg NULL means use whole png.
                {
                    std::cout << "[!] Proj failed to render.\n";
                }
        }
        else
        {
            //std::cout << "[*] Need to get rid of this proj\n";
            game_projectiles.erase(game_projectiles.begin() + i);
        }
        
    }

    // Render Player
    if ( 0 != SDL_RenderCopy(renderer, player->GetTexture(), NULL, player->GetDstRect())) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Player failed to render.\n";
    }

    if ( 0 != SDL_RenderCopy(renderer, player->GetSecondaryFireTexture(), NULL, player->GetSecondaryFirePosition())) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Secondary Fire HUD failed to render.\n";
    }

    if (player->IsSecondaryFireMarkerActive())
    {
        SDL_RenderCopy(renderer, player->GetSecondaryFireMarkerTexture(), NULL, player->GetSecondaryFireMarkerPosition());
    }


    SDL_RenderPresent(renderer);
}

int Graphics::GetScreenWidth()
{
    return screen_width;
}

int Graphics::GetScreenHeight()
{
    return screen_height;
}

void Graphics::BackgroundUpdate(Uint32 loop)
{
    if (clouds1_dest.x >= screen_width || clouds1_dest.y >= (screen_height + 256 )) 
    { 
        clouds1_dest.x = 0; //INSTEAD OF ALWAYS AT ORIGIN, RANDOMIZE 
        clouds1_dest.y = 0;
    }
    
    if (loop % 4 == 0)
    {
        clouds1_dest.x += 1;
        clouds1_dest.y += 2;
    }

    clouds1_animation_index++;
}

SDL_Renderer* Graphics::GetRenderer()
{
    return renderer;
}

// Clean up and quit SDL
void Graphics::cleanup() 
{
    std::cout << "[*] Cleaning up window.\n";

    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window) { SDL_DestroyWindow(window); }
}