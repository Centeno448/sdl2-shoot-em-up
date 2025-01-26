#pragma once

#include <random>

#include "../shootem_math.h"
#include "defs.h"
#include "entity.h"

class Enemy : public Entity {
 public:
  Enemy() : Entity(SCREEN_WIDTH, ShootEmMath::RandomFloat(1, SCREEN_HEIGHT)) {
    dx_ = -(ShootEmMath::RandomFloat(2, 10));
    ResetReloadFrames();
  };

  void DoLogic() override;

  std::string GetEntityId() override;

  bool IsTextureLoaded() override;

  void SetTextureLoaded(bool is_loaded) override;

  void HandleCollision(EntitySharedPtr collided_with) override;

  static void RegisterEnemy();

  std::string GetCollisionLayer() override;

  void Shoot(EntitySharedPtr target);

  void ResetReloadFrames();

  int reload_frames_;

 private:
  inline static const std::string texture_id_ = ENEMY_ENTITY_ID;

  inline static const std::string collides_with_ = BULLET_ENTITY_ID;

  static bool is_texture_loaded_;

  void OnKilled();

  void SpawnExplosion();

  void SpawnDebris();
};
