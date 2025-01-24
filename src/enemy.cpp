#include "enemy.h"

#include "collision_manager.h"
#include "world.h"

void Enemy::DoLogic() {
  if (x_ < -w_) {
    health_ = 0;
  }

  x_ += dx_;
}

std::string Enemy::GetTextureId() { return texture_id_; }

bool Enemy::IsTextureLoaded() { return is_texture_loaded_; }

void Enemy::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
};

bool Enemy::is_texture_loaded_ = false;

void Enemy::RegisterEnemy() {
  EntitySharedPtr entity = World::AddEntityToWorld<Enemy>(
      []() { return std::make_shared<Enemy>(); });

  CollisionManager::layers_.at(BULLET_TEXTURE_ID).push_front(entity);
}

std::string Enemy::GetCollisionLayer() { return collides_with_; }
