#pragma once

#include "effect.h"

class Explosion : public Effect {
 public:
  Explosion(float x, float y);

  void DoLogic() override;

  void Draw(SDL_Renderer* const renderer) override;

  bool IsDone() override;

  bool IsTextureLoaded();

  static void SetTextureLoaded(bool is_loaded);

 private:
  float x_ = 0;
  float y_ = 0;
  float dx_ = 0;
  float dy_ = 0;
  int r_ = 0, g_ = 0, b_ = 0, a_ = 0;
  inline static bool is_texture_loaded_ = false;
};
