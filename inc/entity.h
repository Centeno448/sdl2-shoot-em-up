#pragma once

#include <SDL.h>

#include <memory>
#include <string>

void SDLTextureDeleter(SDL_Texture* renderer);

typedef std::shared_ptr<SDL_Texture> SDLTextureSharedPtr;

class Entity {
 public:
  Entity(float x, float y) : x_(x), y_(y), texture_(nullptr) {};

  float x_;
  float y_;
  float dy_ = 0;
  float dx_ = 0;

  int w_ = 0;
  int h_ = 0;

  float health_;

  virtual void Draw(SDL_Renderer* const);

  virtual void DoLogic();

  void SetTexture(SDL_Texture* texture);

 private:
  SDLTextureSharedPtr texture_;
};
