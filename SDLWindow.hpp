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

    void ShowWindow();

    //Show Window

    // Clean up and quit SDL
    void cleanup();

    void DeactivateWindow();


    // Render content
    void render();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_shown;

    // Initialize SDL, create window and renderer
    bool init(const char* title, int width, int height);

    // Handle input events
    //void handleEvents();

    // Update game logic
    void update();

    

    
};