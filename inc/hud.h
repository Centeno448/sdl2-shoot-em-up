#pragma once

#include <string>

#include "sdl_wrappers.h"

class HUD {
 public:
  static void StaticInit(SDLRendererSharedPtr renderer);

  static void Draw();

  static void ResetScore();

  static void IncreaseScore(unsigned amount);

  static void DrawText(int x, int y, int r, int g, int b,
                       const std::string &&text);

 private:
  static SDL_Renderer *const GetRenderer();
  inline static SDLRendererSharedPtr renderer_ = nullptr;
  inline static int score_ = 0;
  inline static int high_score_ = 0;
};
