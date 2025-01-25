#include "background.h"

#include "defs.h"
#include "texture_manager.h"

void Background::DoLogic() {
  if (--x_ < -SCREEN_WIDTH) {
    x_ = 0;
  }
}

void Background::Draw(SDL_Renderer *const renderer) {
  SDLTextureSharedPtr background =
      TextureManager::GetTextureById(BACKGROUND_TEXTURE_ID);

  SDL_Rect dest;
  int x;

  for (x = x_; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
    dest.x = x;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;

    SDL_RenderCopy(renderer, background.get(), NULL, &dest);
  }
}
