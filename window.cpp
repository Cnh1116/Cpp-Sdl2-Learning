#include <iostream>
#include <SDL2/SDL.h>
#include "window.hpp"

class Window
{
public:
	void Window::Window()
		{
			if ( SDL_Init < 0 )
			{
				std:cout << "[ ERROR ] SDL_Init < 0 ... failed to initialize ... ";
				return -1
			}

			SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, 0);

			if(!window)
			{
				std::cout << "[ ERROR ] Window failed to be created ... exiting ...";
				return -1
			}

			SDL_Surface* window_surface = SDL_GetWindowSurface(window);


			DL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			    if (!renderer) {
				            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
					            SDL_DestroyWindow(window);
						            SDL_Quit();
							            return 1;
								     }

			    SDL_RendererPresent(renderer);
};
