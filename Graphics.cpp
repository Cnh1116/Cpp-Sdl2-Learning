#include "Graphics.hpp"
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Projectiles.hpp"
#include "ItemManager.hpp"

class ItemManager;

// Constructor
Graphics::Graphics(const char* title, int width, int height, int scale)
    : window(nullptr), renderer(nullptr), is_shown(false) , clouds1_animation_index(0)
{
    
    screen_width = width;
    screen_height = height;
    pixel_scale = scale;

    // BACKGROUND STUFF
    clouds1_dest = {0, 0, 576 * 4, 324 * 4}; //FILE SIZE * arbitrary scale factor
    
    if (init(title, width, height)) 
    {
        is_shown = true;
    }

    LoadTextures();

}

// Destructor
Graphics::~Graphics() 
{
    std::cout << "[*] Cleaning up window.\n";

    for (auto& pair : texture_map) 
    {
        SDL_DestroyTexture(pair.second); 
    }
    texture_map.clear();

    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window) { SDL_DestroyWindow(window); }
}

void Graphics::LoadTextures()
{
    // [ LIST OF TEXTURES ]
    // Background
    texture_map["background_texture"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/background-sprites/1.png");
    texture_map["clouds1_texture"] =  GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/background-sprites/3.png");

    // Player
    texture_map["player_main_texture"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/player-sprites/player.png");
    texture_map["player_secondary_fire_hud_texture"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/player-sprites/secondary_fire_hud.png");
    texture_map["player_secondary_fire_marker_texture"] =  GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/player-sprites/secondary_fire_marker.png");

    // Projectiles
    texture_map["primary_fire"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/primary_fire_prime.png");
    texture_map["primary_fire_impact"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/projectile-sprites/secondary_fire_land_effect.png");
    texture_map["secondary_fire"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/projectile-sprites/secondary_fire_projectile_animation.png");
    texture_map["secondary_fire_impact"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/projectile-sprites/secondary_fire_land_effect.png");

    // Items
    texture_map["item_cloud"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/item-sprites/item-cloud.png");
    texture_map["glass_toucan"] = GetTexture("C:/Users/cnh11/OneDrive/Desktop/Cpp-Sdl2-Learning/assets/sprites/item-sprites/glass_toucan4.png");
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
void Graphics::RenderGameItems(Player* player, std::vector<Projectile*> &game_projectiles, std::vector<ItemManager::item>* item_list)
{
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    if (NULL == player->GetDstRect())
    {
        std::cerr << "[!] DstRect for the player is NULL.";
    }


    // Render Background
    if ( 0 != SDL_RenderCopy(renderer, texture_map["background_texture"], NULL, NULL) ) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Background failed to render.\n";
    }

    // Render Background Clouds
    if ( 0 != SDL_RenderCopy(renderer, texture_map["clouds1_texture"], NULL, &clouds1_dest) ) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Background failed to render.\n";
    }

    // Render Items from item vector
    // For item in item list, if their dest rect is withing the bounds of the screen, render it
    for (int i = 0; i < (*item_list).size(); i++)
    {  
        if ((*item_list).at(i).item_dest_rect.x >= 0 && 
        (*item_list).at(i).item_dest_rect.x  <= screen_width - (*item_list).at(i).item_dest_rect.w &&
        (*item_list).at(i).item_dest_rect.y + (*item_list).at(i).item_dest_rect.h >= 0 && 
        (*item_list).at(i).item_dest_rect.y  <= screen_height) 
        {
            if ( 0 != SDL_RenderCopy(renderer, texture_map["item_cloud"], NULL, &(*item_list).at(i).item_cloud_dest_rect)) //Second arg NULL means use whole png.
                {
                    std::cout << "[!] Item failed to render.\n";
                }
            
            if ( 0 != SDL_RenderCopy(renderer, texture_map["glass_toucan"], NULL, &(*item_list).at(i).item_dest_rect)) //Second arg NULL means use whole png.
                {
                    std::cout << "[!] Item failed to render.\n";
                }
        }
        else
        {
            //std::cout << "[*] Need to get rid of this proj\n";
            (*item_list).erase((*item_list).begin() + i);
        }
        
    }


    // Render Enemies from enemy vector

   

    // For Projectile in game_projectiles list, if their dest rect is withing the bounds of the screen, render it
    for (int i = 0; i < game_projectiles.size(); i++)
    {
        // Render Projectiles if they're within the screen
        if (game_projectiles.at(i)->GetDstRect()->x >= 0 && 
        game_projectiles.at(i)->GetDstRect()->x  <= screen_width - game_projectiles.at(i)->GetDstRect()->w &&
        game_projectiles.at(i)->GetDstRect()->y + game_projectiles.at(i)->GetDstRect()->h >= 0 && 
        game_projectiles.at(i)->GetDstRect()->y  <= screen_height) 
        {   

            if (0 != SDL_RenderCopy(renderer, texture_map[game_projectiles.at(i)->GetTextureKey()], game_projectiles.at(i)->GetFrame(), game_projectiles.at(i)->GetDstRect())) //Second arg NULL means use whole png.
                {
                    std::cout << "[!] Proj failed to render.\n";
                }
        }
        // If they're not in the screen delete them
        else
        {
            game_projectiles.at(i)->UpdateState("delete");
        }
        
    }

    // Render Player
    if ( 0 != SDL_RenderCopy(renderer, texture_map["player_main_texture"], NULL, player->GetDstRect())) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Player failed to render.\n";
    }

    if ( 0 != SDL_RenderCopy(renderer, texture_map["player_secondary_fire_hud_texture"], NULL, player->GetSecondaryFirePosition())) //Second arg NULL means use whole png.
    {
        std::cout << "[!] Secondary Fire HUD failed to render.\n";
    }

    if (player->IsSecondaryFireMarkerActive())
    {
        SDL_RenderCopy(renderer, texture_map["player_secondary_fire_marker_texture"], NULL, player->GetSecondaryFireMarkerPosition());
    }


    SDL_RenderPresent(renderer);

    // INCREMENT FRAMES
    // Projectiles
    for (int i = 0; i < game_projectiles.size(); i++)
    {
        
        if (IsFrameDone(game_projectiles.at(i)->frame_time_ms, game_projectiles.at(i)->last_frame_time))
        {
            game_projectiles.at(i)->last_frame_time = SDL_GetTicks();
            if (game_projectiles.at(i)->animation_replayable)
            {
                if (game_projectiles.at(i)->current_frame_index == game_projectiles.at(i)->NumOfFrames() - 1)
                    game_projectiles.at(i)->current_frame_index = 0;
                else
                    game_projectiles.at(i)->AdvanceFrame();
            }

            else
            {
                if (game_projectiles.at(i)->current_frame_index < game_projectiles.at(i)->NumOfFrames() - 1)
                    game_projectiles.at(i)->AdvanceFrame();
            }
        }
    }
    //Items
    for (int i = 0; i < (*item_list).size(); i++)
    {

        //if ((*item_list).at(i).item_dest_rect.x >= 0 &&
    }

    //player
}

int Graphics::GetScreenWidth()
{
    return screen_width;
}

int Graphics::GetScreenHeight()
{
    return screen_height;
}

bool Graphics::IsFrameDone(Uint32 frame_time_ms, Uint32 last_frame_start)
{
    Uint32 current_time = SDL_GetTicks();

    if ((current_time - last_frame_start) >= frame_time_ms)
    {
        return(true);
    }

    else
    {
        //std::cout << "[*] Frame is not done\n";
        return(false);
    }
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

