#include "hud.h"

#include <format>

#include "defs.h"
#include "texture_manager.h"

void HUD::StaticInit(SDLRendererSharedPtr renderer) { renderer_ = renderer; }

SDL_Renderer *const HUD::GetRenderer() { return renderer_.get(); }

void HUD::Draw() {
  DrawText(10, 10, 255, 255, 255, std::format("SCORE: {}", score_));

  if (score_ > high_score_) {
    DrawText(960, 10, 0, 255, 0, std::format("HIGH SCORE: {}", score_));
  } else {
    DrawText(960, 10, 255, 255, 255,
             std::format("HIGH SCORE: {}", high_score_));
  }
}

void HUD::DrawText(int x, int y, int r, int g, int b,
                   const std::string &&text) {
  SDLTextureSharedPtr texture = TextureManager::GetTextureById(FONT_TEXTURE_ID);
  SDL_Rect rect;

  rect.w = GLYPH_WIDTH;
  rect.h = GLYPH_HEIGHT;
  rect.y = 0;

  SDL_SetTextureColorMod(texture.get(), r, g, b);

  for (const char &c : text) {
    if (c >= ' ' && c <= 'Z') {
      rect.x = (c - ' ') * GLYPH_WIDTH;

      SDL_Rect dest;

      dest.x = x;
      dest.y = y;
      dest.w = rect.w;
      dest.h = rect.h;

      SDL_RenderCopy(GetRenderer(), texture.get(), &rect, &dest);

      x += GLYPH_WIDTH;
    }
  }
}

void HUD::ResetScore() {
  if (score_ > high_score_) {
    high_score_ = score_;
  }
  score_ = 0;
}

void HUD::IncreaseScore(unsigned amount) { score_ += amount; }
