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
      player(Player(graphics_manager->GetTexture("assets/sprites/player.png"), graphics_manager->GetTexture("assets/sprites/secondary_fire_hud.png"), PIXEL_SCALE))
{
    // Load Player Sprite
    player.SetPosition( (WINDOW_WIDTH/2) - (player.GetDstRect()->w / 2), WINDOW_HEIGHT - (player.GetDstRect()->h), WINDOW_WIDTH, WINDOW_HEIGHT );

    

     
    // Play Starting Song
    sound_manager->PlayMusic(sound_manager->song_1);
}

void Game::RunGame()
{

    // Game LOOP Specific Pieces
    int loop = 0;
    std::vector<Projectile*> game_projectiles;

    
    while(false == game_over)
    {
        // Get Frame Start Time
        Uint32 current_tick = SDL_GetTicks();
        
        // Handle Events
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            //std::cout << "[*] In RunGame() loop.\n";
            HandleKeyInput(event, &player, game_projectiles);
        }

        // UPDATE NEEDS TO BE A METHOD
        for (Projectile* proj : game_projectiles)
        {
            proj->MoveProjectile();
        }

        // Update player position based on key states
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        float dx = 0, dy = 0;
        if (keystates[SDL_SCANCODE_W])
        {
            dy = -1;
        }
        if (keystates[SDL_SCANCODE_A])
        {
            dx = -1;
        }
        if (keystates[SDL_SCANCODE_S])
        {
            dy = 1;
        }
        if (keystates[SDL_SCANCODE_D])
        {
            dx = 1;
        }

        if (keystates[SDL_SCANCODE_SPACE]) // SPACE //
        {
            
            if(player.IsFireSecondaryReady())
            {
                game_projectiles.push_back(new SecondaryFire(player.GetDstRect()->x, player.GetDstRect()->y,  2, graphics_manager->GetTexture("assets/sprites/secondary_fire_projectile.png"), PIXEL_SCALE));
                sound_manager->PlaySound(sound_manager->sound_2);
                std::cout << "[*] SPACE CLICK  Pressed. \n";
            }
        }

        if (keystates[SDL_SCANCODE_UP]) // UP ARROW //
        {
            
            if(player.IsFirePrimaryReady())
            {
                game_projectiles.push_back(new PrimaryFire(player.GetDstRect()->x, player.GetDstRect()->y, 10.0, graphics_manager->GetTexture("assets/sprites/primary_fire.png"), player.GetBaseDamage(), PIXEL_SCALE));
                sound_manager->PlaySound(sound_manager->sound_1);
                std::cout << "[*] UP Pressed. \n";
            }
        }

        
        
        player.SetPosition(dx * player.GetSpeed(), dy * player.GetSpeed(), WINDOW_WIDTH, WINDOW_HEIGHT);
        
        

        // Render 
         graphics_manager->render(&player, game_projectiles);

        //FPS Control
        //if( (1000.0/MAX_FPS) > (SDL_GetTicks() - loop_start_time) )
        //{
        //    SDL_Delay(  (1000.0/MAX_FPS) > (SDL_GetTicks() - loop_start_time) );
        //}

        // FPS Control Logic
        Uint32 frame_time = SDL_GetTicks() - current_tick;
        if ( (frame_time - current_tick) < ( 1000.0 / MAX_FPS ) )
        {
            SDL_Delay( (1000.0 / MAX_FPS ) - frame_time);
        }

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
            graphics_manager->cleanup();
            SDL_Quit();
            
        }
             
        
        if (event.key.keysym.scancode == SDL_SCANCODE_BACKSLASH) // ` //
        {
            std::cout << "[*] ` Key Pressed.\n";
            
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_TAB) // TAB //
        {
            std::cout << "[*] TAB Key Pressed.\n";
            player->SetSpeed( player->GetSpeed() -1 );
            
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_X) // x //
        {
            std::cout << "[*] X Key Pressed. Incrementing variable.\n";
            times_X_pressed++;
            if ( 9 == ( times_X_pressed % 10 ) )
            {
                std::cout << "[*] X % 10 == 9. Fading Music out and replaying.\n";
                sound_manager->FadeOutMusic();
                sound_manager->PlayMusic(sound_manager->song_1);
            }
        }


}