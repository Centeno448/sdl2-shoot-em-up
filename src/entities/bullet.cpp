#include "entities/bullet.h"

void Bullet::DoLogic() {
  if (x_ > SCREEN_WIDTH) {
    health_ = 0;
  }

  x_ += dx_;
}

std::string Bullet::GetEntityId() { return entity_id_; }

bool Bullet::IsTextureLoaded() { return is_texture_loaded_; }

void Bullet::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
};

void Bullet::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == ENEMY_ENTITY_ID) {
    --health_;
  }
};
