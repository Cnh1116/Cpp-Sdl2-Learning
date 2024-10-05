#include <iostream>
#include "game.hpp"


Game::Game() // Game constructor acts as my INIT function for the game.
    : game_window(new SDLWindow("Main Window", 800, 800, 4)), //Screen name, dimensions and pixel scale
      sound_manager(new SoundManager()),
      game_over(false),
      times_X_pressed(0),
      player(Player(game_window->GetTexture("assets/sprites/player.png")))
{
    // Load Player Sprite
    //player.SetTexture(game_window->GetTexture("assets/sprites/player.png"));

    // Put player bottom middle of screen
    //int HALF_PLAYER_WIDTH = BASE_SPRITE_SIZE * PIXEL_SCALE
    player.SetPosition( (game_window->GetScreenWidth() / 2) - 64, game_window->GetScreenHeight() - 128 );
    

     
    // Play Starting Song
    sound_manager->PlayMusic(sound_manager->song_1);
}

void Game::RunGame()
{
    // GAME VARIABLES, maybe a file for this info ...
    float MAX_FPS = 60.0;
    int PIXEL_SCALE = 2;
    int loop = 0;

    Uint64 current_tick = SDL_GetPerformanceCounter();
    Uint64 last_tick = SDL_GetPerformanceCounter();
    double delta_time = 0.0;

    
    while(false == game_over)
    {
        current_tick = SDL_GetPerformanceCounter();
        delta_time = (double)((current_tick - last_tick) * 1000 / (double)SDL_GetPerformanceFrequency());
        
        // Handle Events
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            std::cout << "[*] In RunGame() loop.\n";
            HandleKeyInput(event, &player);
            
        }

        // UPDATE NEEDS TO BE A METHOD
        // Update player position based on key states
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        float playerSpeed = 5.0f; // Speed in pixels per second
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
        
        player.SetPosition(dx, dy);
        
        

        // Render 
         game_window->render(&player);

        //FPS Control
        //if( (1000.0/MAX_FPS) > (SDL_GetTicks() - loop_start_time) )
        //{
        //    SDL_Delay(  (1000.0/MAX_FPS) > (SDL_GetTicks() - loop_start_time) );
        //}

        last_tick = current_tick;
        loop++;
    }
}

void Game::HandleKeyInput(SDL_Event event, Player* player) //item_vector pointer to spawn item
{

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        
        if (keystates[SDL_SCANCODE_ESCAPE]) // ESC
        {
            std::cout << "[*] Esc Key Pressed. game_over = True\n";
            game_over = true;
            game_window->DeactivateWindow();
            game_window->cleanup();
            SDL_Quit();
            
        }
        
        if (keystates[SDL_SCANCODE_GRAVE]) // `
        {
            std::cout << "[*] ` Key Pressed. Window object set to.\n";
            sound_manager->PlaySound(sound_manager->sound_1);
            
        }

        if (keystates[SDL_SCANCODE_TAB]) // TAB
        {
            std::cout << "[*] TAB Key Pressed.\n";
            
        }

        if (keystates[SDL_SCANCODE_X]) // x
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