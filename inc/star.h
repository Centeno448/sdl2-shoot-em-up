#pragma once

#include "effect_manager.h"

class Star : public Effect {
 public:
  Star(int x, int y, int speed) : x_(x), y_(y), speed_(speed) {}

  void DoLogic() override;
  void Draw(SDL_Renderer* const) override;

 private:
  int x_;
  int y_;
  int speed_;
};
