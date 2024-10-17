#include <iostream>
#include "Game.hpp"
#include <iostream>


int PIXEL_SCALE = 4;
int WINDOW_WIDTH = 2000;
int WINDOW_HEIGHT = 1000;
float MAX_FPS = 60.0;

Game::Game() // Game constructor acts as my INIT function for the game.
    : graphics_manager(new Graphics("Main Window", WINDOW_WIDTH, WINDOW_HEIGHT, PIXEL_SCALE)), //Screen name, dimensions and pixel scale
      sound_manager(new SoundManager()),
      game_over(false),
      times_X_pressed(0),
      item_manager(new ItemManager(graphics_manager)),
      player(Player(graphics_manager, PIXEL_SCALE))
{
    // Load Player Sprite
    player.SetPosition( (WINDOW_WIDTH/2) - (player.GetDstRect()->w / 2), WINDOW_HEIGHT - (player.GetDstRect()->h), WINDOW_WIDTH, WINDOW_HEIGHT );

    

     
    // Play Starting Song
    sound_manager->PlayMusic("first_level_song");
}

Game::~Game()
{
    delete graphics_manager;
    delete sound_manager;
    delete item_manager;
}

void Game::RunGame()
{

    // Game LOOP Specific Pieces
    long loop = 0;
    std::vector<Projectile*> game_projectiles;
    game_projectiles.reserve(30);

    
    while(false == game_over)
    {
        Uint32 current_tick = SDL_GetTicks();
        
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ~  HANDLE Discrete EVENTS    ~
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            //std::cout << "[*] In RunGame() loop.\n";
            HandleKeyInput(event, &player, game_projectiles);
        }

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ~  HANDLE Continous EVENTS    ~
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        float dx = 0, dy = 0;
        if (keystates[SDL_SCANCODE_W])
        {
            dy = -1.0;
        }
        if (keystates[SDL_SCANCODE_A])
        {
            dx = -1.0;
        }
        if (keystates[SDL_SCANCODE_S])
        {
            dy = 1.0;
        }
        if (keystates[SDL_SCANCODE_D])
        {
            dx = 1.0;
        }

        // If we are moving diagnal, we need to normalize the movement
        if (dx != 0 && dy != 0)
        {
            float length = sqrt(dx * dx + dy * dy);
            dx /= length;
            dy /= length;
        }

        if (keystates[SDL_SCANCODE_SPACE]) // SPACE //
        {
            
            if(player.IsFireSecondaryReady())
            {
                player.SetSecondaryFireMarkerActive(true);
                player.SetSecondaryFireMarkerPosition();
                game_projectiles.push_back(new SecondaryFire(player.GetDstRect()->x, player.GetDstRect()->y,  player.GetSecondaryFireSpeed(), PIXEL_SCALE));

                for(int i = 0; i < item_manager->GetItemList()->size(); i++)
                {
                    if (RectRectCollision(player.GetSecondaryFireMarkerPosition(), &item_manager->GetItemList()->at(i).item_coll_rect, false))
                    {
                        std::cout << "[*] Player shot an item!\n";
                        sound_manager->PlaySound("item_collection_sound");
                    }
                }

                sound_manager->PlaySound("player_secondary_fire");
                std::cout << "[*] SPACE CLICK  Pressed. \n";
            }
        }

        if (keystates[SDL_SCANCODE_UP]) // UP ARROW //
        {
            
            if(player.IsFirePrimaryReady())
            {
                // IN ORDER TO MAKE DIFF SIZES WORK, PROJECTILES SHOULD GET ENTIRE SDL REC OT PLAYER / ENEMY. Make the 
                // dest rect of the projectile: X: (player.x + player.w / 2) - (projectile.w / 2)
                // Make collision rect of the projectile = dest rec for now.
                game_projectiles.push_back(new PrimaryFire(player.GetDstRect()->x, player.GetDstRect()->y, 5, player.GetBaseDamage(), 2));
                sound_manager->PlaySound("player_primary_fire");
                std::cout << "[*] UP Pressed. \n";
            }
        }

        /*~~~~~~~~~~~~~~~~~~~~~~~~
        ~  HANDLE COLLISIONS     ~
        ~~~~~~~~~~~~~~~~~~~~~~~~*/
        HandleCollisions(&player, game_projectiles, item_manager->GetItemList());

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ~  UPDATE Players, Projectiles and Enemies     ~
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        graphics_manager->BackgroundUpdate(loop);

        player.Update(dx * player.GetSpeed(), dy * player.GetSpeed(), WINDOW_WIDTH, WINDOW_HEIGHT, loop);

        for (int i = 0; i < game_projectiles.size();)
        {
            game_projectiles.at(i)->Update(); //proj->update() which calles movePRojectile and should ++animation sprite
            if (game_projectiles.at(i)->GetState() == "delete")
            {
                std::cout << "[*] Deleting a projectile.\n";
                delete game_projectiles.at(i);
                game_projectiles.erase(game_projectiles.begin() + i);
            }
            else
            {
                ++i;
            }
        }

        item_manager->UpdateItemList();
        

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ~  RENDER Player, Projectiles and Enemies     ~
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        graphics_manager->RenderGameItems(&player, game_projectiles, item_manager->GetItemList());


        /*~~~~~~~~~~~~~~~~~~~~~~~~
        ~  FPS Control Logic     ~
        ~~~~~~~~~~~~~~~~~~~~~~~~*/
        FPSLogic(current_tick);


        loop++;
    }
}

void Game::HandleKeyInput(SDL_Event event, Player* player, std::vector<Projectile*>& game_projectiles) //item_vector pointer to spawn item
{

        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) // ESC //
        {
            std::cout << "[*] Esc Key Pressed. game_over = True\n";
            game_over = true;
            graphics_manager->DeactivateWindow();
            SDL_Quit();
            
        }
             
        
        if (event.key.keysym.scancode == SDL_SCANCODE_BACKSLASH) // ` //
        {
            std::cout << "[*] ` Key Pressed.\n";
            
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_TAB) // TAB //
        {
            std::cout << "[*] TAB Key Pressed.\n";
            player->SetSpeed( player->GetSpeed() -1.0 );
            
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_X) // x //
        {
            std::cout << "[*] X Key Pressed. Incrementing variable.\n";
            times_X_pressed++;
            if ( 9 == ( times_X_pressed % 10 ) )
            {
                std::cout << "[*] X % 10 == 9. Fading Music out and replaying.\n";
                sound_manager->FadeOutMusic();
                sound_manager->PlayMusic("first_level_song");
            }
        }
}

void Game::HandleCollisions(Player* player, std::vector<Projectile*> &game_projectiles, std::vector<ItemManager::item>* item_list)
{
    
    // CHECKING COLLISIONS FOR DIFF PROJECTILES
    for (int i = 0; i < game_projectiles.size(); i++)
    {  
        if ( dynamic_cast<SecondaryFire*>( game_projectiles.at(i) ) )
        {
            // Once the sec. projectile reaches the sec fire marker, delete it, or play impact animation if it hit item cloud.
            if (RectRectCollision(game_projectiles.at(i)->GetDstRect(), player->GetSecondaryFireMarkerCollision(), false))
            {
                player->SetSecondaryFireMarkerActive(false);

                bool collided_with_item = false;
                for (int j = 0; j < (*item_list).size(); j++)
                {
                    if (RectRectCollision(&(*item_list).at(j).item_coll_rect, game_projectiles.at(i)->GetDstRect(), false))
                    {
                        collided_with_item = true;
                        if (game_projectiles.at(i)->GetState() == "main")
                        {
                            game_projectiles.at(i)->UpdateState("impact");
                        }
                    }
                }
                if (!collided_with_item)
                    game_projectiles.at(i)->UpdateState("delete");

                

                
                
            }

        }
    }
}

bool Game::RectRectCollision(SDL_Rect* rect_1, SDL_Rect* rect_2, bool print_flag)
{
    if (print_flag)
    {
        std::cout << "X: " << rect_1->x << "Y: " << rect_1->y << "W: " << rect_1->w << "H: " << rect_1->h << " VERSUS " 
            << "X: " << rect_2->x << "Y: " << rect_2->y << "W: " << rect_2->w << "H: " << rect_2->h << std::endl;

        std::cout << (rect_1->x < rect_2->x + rect_2->w &&
            rect_1->x + rect_1->w > rect_2->x &&
            rect_1->y < rect_2->y + rect_2->h &&
            rect_1->y + rect_1->h > rect_2->y) << std::endl;
    }
    return (rect_1->x < rect_2->x + rect_2->w &&
            rect_1->x + rect_1->w > rect_2->x &&
            rect_1->y < rect_2->y + rect_2->h &&
            rect_1->y + rect_1->h > rect_2->y);
}

bool Game::RectCircleCollision(SDL_Rect* rect_1, int circle_x, int circle_y, int circle_r)
{
    return true;
}
bool Game::CircleCircleCollision(int circle1_x, int circle1_y, int circle1_r, int circle2_x, int circle2_y, int circle2_r)
{
    return true;
}

void Game::FPSLogic(Uint32 current_tick)
{
    Uint32 frame_time = SDL_GetTicks() - current_tick;
    if ( (frame_time - current_tick) < ( 1000.0 / MAX_FPS ) )
    {
        SDL_Delay( (1000.0 / MAX_FPS ) - frame_time);
    }
}