#include <string>

#include "sdl_wrappers.h"

class HUD {
 public:
  void StaticInit(SDLRendererSharedPtr renderer);

  void DrawText(int x, int y, int r, int g, int b, const std::string &&text);

 private:
  static SDL_Renderer *const GetRenderer();
  inline static SDLRendererSharedPtr renderer_ = nullptr;
  inline static int score_ = 0;
  inline static int high_score_ = 0;
};
