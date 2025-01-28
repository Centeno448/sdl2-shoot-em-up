#pragma once

#include <forward_list>
#include <memory>

#include "defs.h"
#include "effect.h"
#include "sdl_wrappers.h"

class EffectManager {
 public:
  static void DrawEffects();
  static void UpdateEffects();
  static void StaticInit(SDLRendererSharedPtr renderer);

  static void ClearEffects();
  static void ClearEffectsAtLayer(unsigned layer);

  template <typename T, typename F>
  static EffectSharedPtr AddEffect(F f, unsigned layer);

 private:
  static SDL_Renderer* const GetRenderer();
  inline static SDLRendererSharedPtr renderer_ = nullptr;
  inline static int background_x_ = 0;
  inline static std::forward_list<EffectSharedPtr> effects_[MAX_EFFECT_LAYERS] =
      {};
};

template <typename T, typename F>
EffectSharedPtr EffectManager::AddEffect(F f, unsigned layer) {
  if (layer > MAX_EFFECT_LAYERS) {
    layer = 0;
  }

  std::shared_ptr<T> shared_t = f();

  EffectSharedPtr shared_effect = std::static_pointer_cast<Effect>(shared_t);

  effects_[layer].emplace_front(shared_effect);

  return shared_effect;
}
