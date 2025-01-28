#pragma once

#include "defs.h"
#include "entity.h"

class EnemyBullet : public Entity {
 public:
  EnemyBullet(float x, float y) : Entity(x, y) {};

  void DoLogic() override;

  std::string GetEntityId() override;

  void ConfigureEntity() override;

  void HandleCollision(EntitySharedPtr collided_with) override;

 private:
  void ConfigureTexture();

  inline static const std::string entity_id_ = ENEMY_BULLET_ENTITY_ID;
  inline static bool is_texture_loaded_ = false;
};
