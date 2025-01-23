#include "bullet.h"

void Bullet::DoLogic() {
  if (x_ > SCREEN_WIDTH) {
    health_ = 0;
  }

  x_ += dx_;
}

std::string Bullet::GetTextureId() { return texture_id_; }
