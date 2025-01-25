#include "effects/effect_manager.h"

#include "defs.h"
#include "effects/background.h"
#include "effects/star.h"
#include "sdl_wrappers.h"
#include "shootem_math.h"
#include "texture_manager.h"

void EffectManager::StaticInit(SDLRendererSharedPtr renderer) {
  renderer_ = renderer;

  AddEffect<Background>([]() { return std::make_shared<Background>(0); });

  for (int i = 0; i < MAX_STARS; ++i) {
    int x = static_cast<int>(ShootEmMath::RandomNumber(1, SCREEN_WIDTH));
    int y = static_cast<int>(ShootEmMath::RandomNumber(1, SCREEN_HEIGHT));
    int speed = static_cast<int>(ShootEmMath::RandomNumber(1.0, 9.0));

    AddEffect<Star>(
        [x, y, speed]() { return std::make_shared<Star>(x, y, speed); });
  }
}

void EffectManager::UpdateEffects() {
  for (EffectSharedPtr &e : effects_) {
    e->DoLogic();
  }
}

SDL_Renderer *const EffectManager::GetRenderer() { return renderer_.get(); }

void EffectManager::DrawEffects() {
  for (EffectSharedPtr &e : effects_) {
    e->Draw(GetRenderer());
  }
}
