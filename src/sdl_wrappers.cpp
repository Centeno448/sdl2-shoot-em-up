#include "sdl_wrappers.h"

#include "log.h"

void SDLTextureDeleter(SDL_Texture* texture) { SDL_DestroyTexture(texture); }

void SDLRendererDeleter(SDL_Renderer* renderer) {
  SDL_DestroyRenderer(renderer);
}

void SDLWindowDeleter(SDL_Window* window) { SDL_DestroyWindow(window); }
