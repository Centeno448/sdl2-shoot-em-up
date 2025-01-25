#include "effect_manager.h"

#include "defs.h"
#include "sdl_wrappers.h"
#include "shootem_math.h"
#include "star.h"
#include "texture_manager.h"

void EffectManager::StaticInit(SDLRendererSharedPtr renderer) {
  renderer_ = renderer;

  for (int i = 0; i < MAX_STARS; ++i) {
    int x = static_cast<int>(ShootEmMath::RandomNumber(1, SCREEN_WIDTH));
    int y = static_cast<int>(ShootEmMath::RandomNumber(1, SCREEN_HEIGHT));
    int speed = static_cast<int>(ShootEmMath::RandomNumber(1.0, 9.0));

    AddEffect<Star>(
        [x, y, speed]() { return std::make_shared<Star>(x, y, speed); });
  }
}

void EffectManager::UpdateEffects() {
  if (--background_x_ < -SCREEN_WIDTH) {
    background_x_ = 0;
  }

  for (EffectSharedPtr &e : effects_) {
    e->DoLogic();
  }
}

SDL_Renderer *const EffectManager::GetRenderer() { return renderer_.get(); }

void EffectManager::DrawEffects() {
  DrawBackground();
  for (EffectSharedPtr &e : effects_) {
    e->Draw(GetRenderer());
  }
}

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
