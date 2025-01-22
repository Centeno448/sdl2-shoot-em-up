#pragma once

#include <SDL.h>

#include <memory>
#include <string>

#include "app.h"

void SDLTextureDeleter(SDL_Texture* renderer);

typedef std::unique_ptr<SDL_Texture, decltype(&SDLTextureDeleter)>
    SDLTextureUniquePtr;

class Entity {
 public:
  Entity(int x, int y, const App& app, const std::string& texture_path)
      : x_(x), y_(y), app_(app), texture_(nullptr, &SDLTextureDeleter) {
    SetTexture(texture_path);
  };

  int x_;
  int y_;

  void DrawTexture();

 private:
  bool SetTexture(const std::string path);
  const App& app_;
  SDLTextureUniquePtr texture_;
};
