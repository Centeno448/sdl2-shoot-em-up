#include "sdl_wrappers.h"

#include "log.h"

void SDLTextureDeleter(SDL_Texture* texture) { SDL_DestroyTexture(texture); }

void SDLRendererDeleter(SDL_Renderer* renderer) {
  SDL_DestroyRenderer(renderer);
}

void SDLWindowDeleter(SDL_Window* window) { SDL_DestroyWindow(window); }

void SDLMixChunkDeleter(Mix_Chunk* mix_chunk) { Mix_FreeChunk(mix_chunk); }

void SDLMixMusicDeleter(Mix_Music* mix_music) {
  if (mix_music != nullptr) {
    Mix_HaltMusic();
    Mix_FreeMusic(mix_music);
  }
}
