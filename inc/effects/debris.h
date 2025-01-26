#pragma once

#include <SDL.h>

#include "effect.h"

class Debris : public Effect {
 public:
  Debris(SDL_Rect entity, SDL_Rect me, SDLTextureSharedPtr texture);

  void DoLogic() override;

  void Draw(SDL_Renderer* const renderer) override;

  bool IsDone() override;

 private:
  float x_;
  float y_;
  float dx_;
  float dy_;
  SDL_Rect rect_;
  SDLTextureSharedPtr texture_;
  int life_;
};
