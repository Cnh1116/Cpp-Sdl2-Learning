#include "SDLWindow.hpp"
#include <iostream>

// Constructor
SDLWindow::SDLWindow(const char* title, int width, int height)
    : window(nullptr), renderer(nullptr), is_shown(false) 
{
    if (init(title, width, height)) 
    {
        is_shown = true;
    }
}

// Destructor
SDLWindow::~SDLWindow() 
{
    cleanup();
}

void SDLWindow::HideWindow()
{
    std::cout << "[*] HideWindow() Called";
    is_shown = false;
    SDL_HideWindow(window);  
}

void SDLWindow::ShowWindow()
{
    std::cout << "[*] ShowWindow() Called";
    is_shown = true;
    SDL_ShowWindow(window);
}

void SDLWindow::DeactivateWindow()
{
    is_shown = false;
}

// Initialize SDL, create window and renderer
bool SDLWindow::init(const char* title, int width, int height) 
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
        std::cerr << "Window creation error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) 
    {
        std::cerr << "Renderer creation error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}


/*// Handle input events
void SDLWindow::handleEvents() 
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) 
        {
            isRunning = false;
        }
        
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                std::cout << "[*] Esc Key Pressed. Window object set to isRunning = False\n";
                isRunning = false;
            }
        }
    }
}*/

// Update game logic
void SDLWindow::update() 
{

}

// Render content
void SDLWindow::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Any drawing logic would go here

    SDL_RenderPresent(renderer);
}

// Clean up and quit SDL
void SDLWindow::cleanup() 
{
    std::cout << "[*] Cleaning up window.";

    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window) { SDL_DestroyWindow(window); }
}