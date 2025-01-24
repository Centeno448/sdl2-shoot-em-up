#include <SDL.h>

#include <memory>

void SDLTextureDeleter(SDL_Texture* texture);

void SDLRendererDeleter(SDL_Renderer* renderer);

void SDLWindowDeleter(SDL_Window* window);

typedef std::shared_ptr<SDL_Texture> SDLTextureSharedPtr;

typedef std::shared_ptr<SDL_Renderer> SDLRendererSharedPtr;

typedef std::unique_ptr<SDL_Window, decltype(&SDLWindowDeleter)>
    SDLWindowUniquePtr;
