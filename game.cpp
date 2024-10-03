#include <iostream>
#include "game.hpp"

Game::Game()
    : game_window(new SDLWindow("Main Window", 800, 600)),  // Create a new SDLWindow object on the heap
      debug_window(new SDLWindow("Secondary Window", 640, 480))
{
}

void Game::RunGame()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        game_window->run();
        debug_window->run();

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                std::cout << "[*] Esc Key Pressed. Window object set to isRunning = False\n";
                game_window->cleanup();
                debug_window->cleanup();
            }
            
            if (event.key.keysym.sym == SDLK_BACKQUOTE)
            {
                std::cout << "[*] ` Key Pressed. Window object set to.\n";
            }
        }
        
     
    }
}