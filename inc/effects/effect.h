#pragma once

#include <memory>

#include "sdl_wrappers.h"

class Effect {
 public:
  virtual void DoLogic() {};

  virtual void Draw(SDL_Renderer* const renderer) {};

  virtual bool IsDone() { return false; };
};

typedef std::shared_ptr<Effect> EffectSharedPtr;
