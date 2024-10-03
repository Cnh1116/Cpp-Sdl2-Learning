#include "SDLWindow.hpp"
#include <iostream>

// Constructor
SDLWindow::SDLWindow(const char* title, int width, int height)
    : window(nullptr), renderer(nullptr), isRunning(false) 
{
    if (init(title, width, height)) 
    {
        isRunning = true;
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
    SDL_HideWindow(window);
    isRunning = false;
}

// Initialize SDL, create window and renderer
bool SDLWindow::init(const char* title, int width, int height) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
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


// Handle input events
void SDLWindow::handleEvents() 
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
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

            if (event.key.keysym.sym == SDLK_BACKQUOTE)
            {
                std::cout << "[*] ` Key Pressed. Window object set to.\n";
               
            }
        }
    }
}

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
    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window) { SDL_DestroyWindow(window); }
    SDL_Quit();
}

// Main loop
void SDLWindow::run() 
{
    while (isRunning) 
    {
        handleEvents();
        update();
        render();
    }
}