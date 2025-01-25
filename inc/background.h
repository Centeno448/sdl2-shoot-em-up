#pragma once

#include "effect_manager.h"

class Background : public Effect {
 public:
  Background(int x) : x_(x) {}

  void DoLogic() override;

  void Draw(SDL_Renderer* const) override;

 private:
  int x_;
};
