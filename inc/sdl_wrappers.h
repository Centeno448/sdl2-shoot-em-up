#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <memory>

void SDLTextureDeleter(SDL_Texture* texture);

void SDLRendererDeleter(SDL_Renderer* renderer);

void SDLWindowDeleter(SDL_Window* window);

void SDLMixChunkDeleter(Mix_Chunk* mix_chunk);

void SDLMixMusicDeleter(Mix_Music* mix_music);

typedef std::shared_ptr<SDL_Texture> SDLTextureSharedPtr;

typedef std::shared_ptr<SDL_Renderer> SDLRendererSharedPtr;

typedef std::unique_ptr<SDL_Window, decltype(&SDLWindowDeleter)>
    SDLWindowUniquePtr;

typedef std::shared_ptr<Mix_Chunk> SDLMixChunkSharedPtr;

typedef std::unique_ptr<Mix_Music, decltype(&SDLMixMusicDeleter)>
    SDLMixMusicUniquePtr;
