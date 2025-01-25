#include "effect_manager.h"

#include "defs.h"
#include "sdl_wrappers.h"
#include "texture_manager.h"

void EffectManager::StaticInit(SDLRendererSharedPtr renderer) {
  renderer_ = renderer;
}

void EffectManager::UpdateEffects() {
  if (--background_x_ < -SCREEN_WIDTH) {
    background_x_ = 0;
  }
}

SDL_Renderer *const EffectManager::GetRenderer() { return renderer_.get(); }

void EffectManager::DrawEffects() { DrawBackground(); }

void EffectManager::DrawBackground() {
  SDLTextureSharedPtr background =
      TextureManager::GetTextureById(BACKGROUND_TEXTURE_ID);

  SDL_Rect dest;
  int x;

  for (x = background_x_; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
    dest.x = x;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;

    SDL_RenderCopy(GetRenderer(), background.get(), NULL, &dest);
  }
}
