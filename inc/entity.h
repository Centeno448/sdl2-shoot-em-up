#pragma once

#include <SDL.h>

#include <memory>
#include <string>

void SDLTextureDeleter(SDL_Texture* renderer);

typedef std::unique_ptr<SDL_Texture, decltype(&SDLTextureDeleter)>
    SDLTextureUniquePtr;

class Entity {
 public:
  Entity(int x, int y) : x_(x), y_(y), texture_(nullptr, &SDLTextureDeleter) {};

  int x_;
  int y_;

  void DrawTexture(SDL_Renderer* const);
  bool SetTexture(SDL_Renderer* const, const std::string path);

 private:
  SDLTextureUniquePtr texture_;
};
