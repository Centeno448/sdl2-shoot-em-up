#pragma once

#include <forward_list>
#include <memory>

#include "effect.h"
#include "sdl_wrappers.h"

class EffectManager {
 public:
  static void DrawEffects();
  static void UpdateEffects();
  static void StaticInit(SDLRendererSharedPtr renderer);

  template <typename T, typename F>
  static EffectSharedPtr AddEffect(F f);

 private:
  static SDL_Renderer* const GetRenderer();
  static void DrawBackground();
  inline static SDLRendererSharedPtr renderer_ = nullptr;
  inline static int background_x_ = 0;
  inline static std::forward_list<EffectSharedPtr> effects_ = {};
};

template <typename T, typename F>
EffectSharedPtr EffectManager::AddEffect(F f) {
  std::shared_ptr<T> shared_t = f();

  EffectSharedPtr shared_effect = std::static_pointer_cast<Effect>(shared_t);

  effects_.emplace_front(shared_effect);

  return shared_effect;
}
