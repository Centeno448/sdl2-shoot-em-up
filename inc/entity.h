#pragma once

#include <SDL.h>

#include <memory>
#include <string>

#include "texture_manager.h"

class Entity {
 public:
  Entity(float x, float y) : x_(x), y_(y) {};

  float x_;
  float y_;
  float dy_ = 0;
  float dx_ = 0;

  int w_ = 0;
  int h_ = 0;

  float health_;

  virtual void Draw(SDL_Renderer* const);

  virtual void DoLogic();

  virtual std::string GetTextureId();
  SDLTextureSharedPtr texture_ = nullptr;
};
