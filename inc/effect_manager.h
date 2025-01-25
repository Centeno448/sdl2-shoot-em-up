#pragma once

#include "sdl_wrappers.h"

class EffectManager {
 public:
  static void DrawEffects();
  static void UpdateEffects();
  static void StaticInit(SDLRendererSharedPtr renderer);

 private:
  static SDL_Renderer* const GetRenderer();
  static void DrawBackground();
  inline static SDLRendererSharedPtr renderer_ = nullptr;
  inline static int background_x_ = 0;
};
