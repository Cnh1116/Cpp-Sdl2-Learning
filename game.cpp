#include <iostream>
#include "game.hpp"
Game::Game()
    : game_window(new SDLWindow("Main Window", 800, 600)),
      sound_manager(new SoundManager()),
      game_over(false),
      times_X_pressed(0)
{
     sound_manager->PlayMusic(sound_manager->song_1);
}

void Game::RunGame()
{
    
  
   
    while(false == game_over)
    {
        game_window->render();

        

        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            std::cout << "[*] In RunGame() loop.\n";
            HandleKeyInput(event);
            
        }
    }
}

void Game::HandleKeyInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // ESC
                    {
                        std::cout << "[*] Esc Key Pressed. Window object set to isRunning = False\n";
                        game_over = true;
                        game_window->DeactivateWindow();
                        game_window->cleanup();
                        SDL_Quit();
                        break;
                    }
                    
                    case SDLK_BACKQUOTE: // `
                    {
                        std::cout << "[*] ` Key Pressed. Window object set to.\n";
                        sound_manager->PlaySound(sound_manager->sound_1);
                        break;
                    }

                    case SDLK_TAB: // TAB
                    {
                        std::cout << "[*] TAB Key Pressed. Fading Music Out, then playing it again.";
                        break;
                    }

                    case SDLK_x: // TAB
                    {
                        std::cout << "[*] X Key Pressed. Incrementing variable.";
                        times_X_pressed++;
                        if ( 9 == ( times_X_pressed % 10 ) )
                        {
                            std::cout << "[*] X%10 == 9. Fading Music out and replaying.";
                            sound_manager->FadeOutMusic();
                            sound_manager->PlayMusic(sound_manager->song_1);
                        }
                        break;
                    }

                    default:
                        std::cout << "[*] Key pressed that is not in the RunGame switch statement.";
                        break;
                } 
            }
}