#include "star.h"

void Star::DoLogic() {
  x_ -= speed_;

  if (x_ < 0) {
    x_ = SCREEN_WIDTH + x_;
  }
}

void Star::Draw(SDL_Renderer *const renderer) {
  int c = 32 * speed_;

  SDL_SetRenderDrawColor(renderer, c, c, c, 255);

  SDL_RenderDrawLine(renderer, x_, y_, x_ + 3, y_);
}
