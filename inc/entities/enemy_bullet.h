#pragma once

#include "defs.h"
#include "entity.h"

class EnemyBullet : public Entity {
 public:
  EnemyBullet(float x, float y) : Entity(x, y) {};

  void DoLogic() override;

  std::string GetEntityId() override;

  bool IsTextureLoaded() override;

  void SetTextureLoaded(bool is_loaded) override;

  void HandleCollision(EntitySharedPtr collided_with) override;

 private:
  inline static const std::string texture_id_ = ENEMY_BULLET_ENTITY_ID;
  static bool is_texture_loaded_;
};
