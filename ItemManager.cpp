#include "ItemManager.hpp"
#include <iostream>
#include "Graphics.hpp"



ItemManager::ItemManager(Graphics* graphics_manager)
{
    time_last_item_spawned = 0;
    item_cloud_texture=  graphics_manager->GetTexture(item_cloud_png);
    glass_toucan_texture =  graphics_manager->GetTexture(glass_toucan_png);
}

std::vector<ItemManager::item>* ItemManager::GetItemList()
{
    return &item_list;
}

void ItemManager::UpdateItemList() // This is where the logic of when to spawn items occurs and moving them downwards.
{
    Uint32 current_time = SDL_GetTicks();

    if ( (current_time - time_last_item_spawned) >= cooldown_item_spawn_ms )
    {
        SDL_Rect spawn_location = {500, 0, 32, 32}; //32 IS BASE SPRITE SIZE

        SDL_Rect tmp_item_dest_rect = {spawn_location.x, spawn_location.y, spawn_location.w * 2, spawn_location.h * 2};
        SDL_Rect tmp_item_cloud_dest_rect = {tmp_item_dest_rect.x - (tmp_item_dest_rect.w / 2), tmp_item_dest_rect.y - (tmp_item_dest_rect.h / 2), tmp_item_dest_rect.w * 2, tmp_item_dest_rect.h * 2};
        SDL_Rect tmp_item_coll_rect = {spawn_location.x, spawn_location.y, spawn_location.w, spawn_location.h};

        item_list.push_back({glass_toucan_texture, tmp_item_dest_rect, tmp_item_coll_rect,  item_cloud_texture, tmp_item_cloud_dest_rect});
        time_last_item_spawned = current_time;
    }

    else
    {
        //std::cout << "[*] Waiting to spawn an item\n";
    }

    for (int i = 0; i < item_list.size(); i++)
    {  
        item_list.at(i).item_dest_rect.y += 1;
        item_list.at(i).item_cloud_dest_rect.y += 1;
        item_list.at(i).item_coll_rect.y += 1;
    }
}

SDL_Texture* ItemManager::GetItemCloudTexture()
{
    return item_cloud_texture;
}
