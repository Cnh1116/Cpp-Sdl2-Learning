#include <iostream>
#include "game.hpp"

Game::Game()
    : game_window(new SDLWindow("Main Window", 800, 600)),
      sound_manager(new SoundManager()),
      game_over(false)
{}

void Game::RunGame()
{
    while(false == game_over)
    {
        game_window->render();

        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            std::cout << "[*] In RunGame() loop.\n";
            if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        std::cout << "[*] Esc Key Pressed. Window object set to isRunning = False\n";
                        game_over = true;
                        game_window->DeactivateWindow();
                        game_window->cleanup();
                        SDL_Quit();
                        break;
                    }
                    
                    case SDLK_BACKQUOTE:
                    {
                        std::cout << "[*] ` Key Pressed. Window object set to.\n";
                        sound_manager->PlaySound("/home/monkey-d-luffy/Cpp-Sdl2-Learning/video-game-sounds/sounds/mixkit-arcade-mechanical-bling-210.wav");
                        break;
                    }

                    default:
                        std::cout << "[*] Key pressed that is not in the RunGame switch statement.";
                }


                
            }
        }
    }
}