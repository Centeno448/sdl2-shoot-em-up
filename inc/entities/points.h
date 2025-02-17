#pragma once

#include "defs.h"
#include "entity.h"
#include "shootem_math.h"

class Points : public Entity {
 public:
  Points(float x, float y, float dx) : Entity(x, y) {
    health_ = FPS_TARGET * 4;
    dx_ = dx;
    dy_ = ShootEmMath::RandomFloat(-6, 6);
  };

  void DoLogic() override;

  std::string GetEntityId() override;

  void ConfigureEntity() override;

  void HandleCollision(EntitySharedPtr collided_with) override;

  static EntitySharedPtr Spawn(float x, float y, float dx, int h);

 private:
  void ConfigureTexture();

  inline static const std::string entity_id_ = POINTS_ENTITY_ID;

  inline static bool is_texture_loaded_ = false;
};
