#include "effects/debris.h"

#include "defs.h"
#include "shootem_math.h"

void Debris::DoLogic() {
  x_ += dx_;
  y_ += dy_;

  dy_ += 0.5;

  --life_;
}

void Debris::Draw(SDL_Renderer* const renderer) {
  SDL_Rect dest;

  dest.x = static_cast<int>(x_);
  dest.y = static_cast<int>(y_);
  dest.w = static_cast<int>(rect_.w);
  dest.h = static_cast<int>(rect_.h);

  SDL_RenderCopy(renderer, texture_.get(), &rect_, &dest);
}

bool Debris::IsDone() { return life_ <= 0; }

Debris::Debris(SDL_Rect source, SDL_Rect debris_shard,
               SDLTextureSharedPtr texture) {
  x_ = static_cast<float>(source.x + source.w / 2);
  y_ = static_cast<float>(source.y + source.h / 2);
  dx_ = (ShootEmMath::RandomFloat(0, 6)) - (ShootEmMath::RandomFloat(0, 6));
  dy_ = -(5 + (ShootEmMath::RandomFloat(0, 13)));
  life_ = FPS_TARGET * 2;
  texture_ = texture;

  rect_ = debris_shard;
}
