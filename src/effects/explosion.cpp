#include "effects/explosion.h"

#include "defs.h"
#include "shootem_math.h"
#include "texture_manager.h"

Explosion::Explosion(float x, float y) {
  x_ = x;
  y_ = y;
  x_ = x_ + (ShootEmMath::RandomFloat(0, 33)) -
       (ShootEmMath::RandomFloat(0, 33));
  y_ = y_ + (ShootEmMath::RandomFloat(0, 33)) -
       (ShootEmMath::RandomFloat(0, 33));

  dx_ = (ShootEmMath::RandomFloat(0, 11)) - (ShootEmMath::RandomFloat(0, 11));
  dy_ = (ShootEmMath::RandomFloat(0, 11)) - (ShootEmMath::RandomFloat(0, 11));

  dx_ /= 10.0;
  dy_ /= 10.0;

  switch (ShootEmMath::RandomInt(0, 3)) {
    case 0:
      r_ = 255;
      break;

    case 1:
      r_ = 255;
      g_ = 128;
      break;

    case 2:
      r_ = 255;
      g_ = 255;
      break;

    default:
      r_ = 255;
      g_ = 255;
      b_ = 255;
      break;
  }

  a_ = ShootEmMath::RandomInt(0, FPS_TARGET * 3);
}

void Explosion::DoLogic() {
  x_ += dx_;
  y_ += dy_;

  --a_;
}

void Explosion::Draw(SDL_Renderer *const renderer) {
  SDLTextureSharedPtr explosion =
      TextureManager::GetTextureById(EXPLOSION_TEXTURE_ID);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
  SDL_SetTextureBlendMode(explosion.get(), SDL_BLENDMODE_ADD);

  SDL_SetTextureColorMod(explosion.get(), r_, g_, b_);
  SDL_SetTextureAlphaMod(explosion.get(), a_);

  SDL_Rect dest;

  dest.x = static_cast<int>(x_);
  dest.y = static_cast<int>(y_);
  SDL_QueryTexture(explosion.get(), NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(renderer, explosion.get(), NULL, &dest);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

bool Explosion::IsTextureLoaded() { return is_texture_loaded_; }

void Explosion::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
}

bool Explosion::IsDone() { return a_ <= 0; }
