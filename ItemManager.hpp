#ifndef ITEMMANAGER_HPP
#define ITEMMANAGER_HPP

#include <SDL2/SDL.h>
#include <vector>

class Graphics;

class ItemManager
{
    
    public:
       struct item
        {
            SDL_Texture* item_texture;
            SDL_Rect item_dest_rect;
            SDL_Rect item_coll_rect;
            SDL_Texture* item_cloud_texture;
            SDL_Rect item_cloud_dest_rect;
            // rarity?
        };

        ItemManager(Graphics* graphics_manager);
        std::vector<item>* GetItemList();
        void UpdateItemList(); // This is where the logic of when to spawn items occurs.
        SDL_Texture* GetItemCloudTexture();

    private:
        const char* item_cloud_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sprites/item-sprites/item-cloud.png";
        SDL_Texture* item_cloud_texture;

        Uint32 time_last_item_spawned;
        Uint32 cooldown_item_spawn_ms = 2000;

        //ITEMS
        SDL_Texture* glass_toucan_texture;
        const char*  glass_toucan_png = "/home/monkey-d-luffy/Cpp-Sdl2-Learning/assets/sprites/item-sprites/glass_toucan4.png";

        std::vector<item> item_list;



 

};

#endif