#include "enemy.h"

#include "collision_manager.h"
#include "enemy_bullet.h"
#include "shootem_math.h"
#include "world.h"

void Enemy::DoLogic() {
  if (x_ < -w_) {
    health_ = 0;
  }

  EntitySharedPtr player = World::GetEntityById("PLYR");

  if (player != nullptr) {
    if (reload_frames_ <= 0) {
      Shoot(player);
      ResetReloadFrames();
    } else {
      --reload_frames_;
    }
  }

  x_ += dx_;
}

std::string Enemy::GetEntityId() { return texture_id_; }

bool Enemy::IsTextureLoaded() { return is_texture_loaded_; }

void Enemy::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
};

bool Enemy::is_texture_loaded_ = false;

void Enemy::RegisterEnemy() {
  EntitySharedPtr entity = World::AddEntityToWorld<Enemy>(
      []() { return std::make_shared<Enemy>(); });

  CollisionManager::layers_.at(BULLET_ENTITY_ID).push_front(entity);
}

void Enemy::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == "BLLT") {
    --health_;
  }
};

void Enemy::Shoot(EntitySharedPtr target) {
  // Spawn bullet
  EntitySharedPtr bullet = World::AddEntityToWorld<EnemyBullet>(
      [this]() { return std::make_shared<EnemyBullet>(x_ + (h_ / 2), y_); });

  // TODO: Stop app on failure to spawn bullet

  bullet->y_ += (h_ / 2) - (bullet->h_ / 2);

  ShootEmMath::CalculateSlope(target->x_, target->y_, x_, y_, bullet->dx_,
                              bullet->dy_);

  bullet->dx_ *= ENEMY_BULLET_SPEED;
  bullet->dy_ *= ENEMY_BULLET_SPEED;
}

void Enemy::ResetReloadFrames() {
  reload_frames_ =
      static_cast<int>(ShootEmMath::RandomNumber(10.0, FPS_TARGET * 2.0));
}

std::string Enemy::GetCollisionLayer() { return collides_with_; }
