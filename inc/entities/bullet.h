#pragma once

#include "defs.h"
#include "entity.h"

class Bullet : public Entity {
 public:
  Bullet(float x, float y) : Entity(x, y) { dx_ = PLAYER_BULLET_SPEED; };

  void DoLogic() override;

  std::string GetEntityId() override;

  void ConfigureEntity() override;

  void HandleCollision(EntitySharedPtr collided_with) override;

 private:
  void ConfigureTexture();

  inline static const std::string entity_id_ = BULLET_ENTITY_ID;
  inline static bool is_texture_loaded_ = false;
};
