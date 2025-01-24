#include "bullet.h"

void Bullet::DoLogic() {
  if (x_ > SCREEN_WIDTH) {
    health_ = 0;
  }

  x_ += dx_;
}

std::string Bullet::GetTextureId() { return texture_id_; }

bool Bullet::IsTextureLoaded() { return is_texture_loaded_; }

void Bullet::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
};

bool Bullet::is_texture_loaded_ = false;
