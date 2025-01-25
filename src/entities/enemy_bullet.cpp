#include "entities/enemy_bullet.h"

void EnemyBullet::DoLogic() {
  if (x_ < -w_ || x_ > SCREEN_WIDTH || y_ < -h_ || y_ > SCREEN_HEIGHT) {
    health_ = 0;
  }

  x_ += dx_;
  y_ += dy_;
}

std::string EnemyBullet::GetEntityId() { return texture_id_; }

bool EnemyBullet::IsTextureLoaded() { return is_texture_loaded_; }

void EnemyBullet::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
};

void EnemyBullet::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == "PLYR") {
    --health_;
  }
};

bool EnemyBullet::is_texture_loaded_ = false;
