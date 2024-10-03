#include <SDL2/SDL.h>

class SDLWindow 
{
public:
    // Constructor
    SDLWindow(const char* title, int width, int height);

    // Destructor
    ~SDLWindow();

    //Hide Window 
    void HideWindow();

    //Show Window

    // Clean up and quit SDL
    void cleanup();


    // Main loop
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    // Initialize SDL, create window and renderer
    bool init(const char* title, int width, int height);

    // Handle input events
    void handleEvents();

    // Update game logic
    void update();

    // Render content
    void render();

    
};