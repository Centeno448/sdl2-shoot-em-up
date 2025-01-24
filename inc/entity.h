#pragma once

#include <SDL.h>

#include <memory>
#include <string>

#include "texture_manager.h"

class Entity {
 public:
  Entity(float x, float y) : x_(x), y_(y), health_(1) {};

  ~Entity() { texture_.reset(); }

  float x_;
  float y_;
  float dy_ = 0;
  float dx_ = 0;

  int w_ = 0;
  int h_ = 0;

  float health_;

  virtual bool IsDead();

  virtual void Draw(SDL_Renderer* const);

  virtual void DoLogic();

  virtual bool IsTextureLoaded();

  virtual void SetTextureLoaded(bool is_loaded);

  virtual std::string GetTextureId();

  SDLTextureSharedPtr texture_ = nullptr;
};

typedef std::shared_ptr<Entity> EntitySharedPtr;
