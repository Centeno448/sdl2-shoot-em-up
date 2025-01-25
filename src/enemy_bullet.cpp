#include "enemy_bullet.h"

void EnemyBullet::DoLogic() {
  if (x_ < -w_) {
    health_ = 0;
  }

  x_ += dx_;
  y_ += dy_;
}

std::string EnemyBullet::GetTextureId() { return texture_id_; }

bool EnemyBullet::IsTextureLoaded() { return is_texture_loaded_; }

void EnemyBullet::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
};

void EnemyBullet::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetTextureId() == "PLYR") {
    --health_;
  }
};

bool EnemyBullet::is_texture_loaded_ = false;
