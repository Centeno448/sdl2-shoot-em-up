#include "effects/effect_manager.h"

#include "defs.h"
#include "effects/background.h"
#include "effects/star.h"
#include "sdl_wrappers.h"
#include "shootem_math.h"
#include "texture_manager.h"

void EffectManager::StaticInit(SDLRendererSharedPtr renderer) {
  renderer_ = renderer;

  for (int i = 0; i < MAX_STARS; ++i) {
    int x = static_cast<int>(ShootEmMath::RandomFloat(1, SCREEN_WIDTH));
    int y = static_cast<int>(ShootEmMath::RandomFloat(1, SCREEN_HEIGHT));
    int speed = static_cast<int>(ShootEmMath::RandomFloat(1.0, 9.0));

    AddEffect<Star>(
        [x, y, speed]() { return std::make_shared<Star>(x, y, speed); }, 0);
  }

  AddEffect<Background>([]() { return std::make_shared<Background>(0); }, 0);
}

void EffectManager::UpdateEffects() {
  for (int i = 0; i < MAX_EFFECT_LAYERS; ++i) {
    auto current_effect = effects_[i].begin();
    while (current_effect != effects_[i].end()) {
      if ((*current_effect)->IsDone()) {
        EffectSharedPtr to_delete = (*current_effect);
        ++current_effect;
        effects_[i].remove(to_delete);
      } else {
        (*current_effect)->DoLogic();
        ++current_effect;
      }
    }
  }
}

SDL_Renderer *const EffectManager::GetRenderer() { return renderer_.get(); }

void EffectManager::DrawEffects() {
  for (int i = 0; i < MAX_EFFECT_LAYERS; ++i) {
    for (EffectSharedPtr &e : effects_[i]) {
      e->Draw(GetRenderer());
    }
  }
}
