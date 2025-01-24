#pragma once

#include <random>

#include "defs.h"
#include "entity.h"
#include "shootem_math.h"

class Enemy : public Entity {
 public:
  Enemy() : Entity(SCREEN_WIDTH, ShootEmMath::RandomNumber(1, SCREEN_HEIGHT)) {
    dx_ = -(ShootEmMath::RandomNumber(2, 10));
  };

  void DoLogic() override;

  std::string GetTextureId() override;

  bool IsTextureLoaded() override;

  void SetTextureLoaded(bool is_loaded) override;

  void HandleCollision(EntitySharedPtr collided_with) override;

  static void RegisterEnemy();

  std::string GetCollisionLayer() override;

 private:
  inline static const std::string texture_id_ = ENEMY_TEXTURE_ID;

  inline static const std::string collides_with_ = BULLET_TEXTURE_ID;

  static bool is_texture_loaded_;
};
