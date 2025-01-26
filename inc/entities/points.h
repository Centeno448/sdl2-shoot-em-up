#pragma once

#include "defs.h"
#include "entity.h"

class Points : public Entity {
 public:
  Points(float x, float y, float dx) : Entity(x, y) {
    health_ = 1;
    dx_ = dx;
  };

  void DoLogic() override;

  std::string GetEntityId() override;

  bool IsTextureLoaded() override;

  void SetTextureLoaded(bool is_loaded) override;

  void HandleCollision(EntitySharedPtr collided_with) override;

  static EntitySharedPtr Spawn(float x, float y, float dx, int h);

 private:
  inline static const std::string entity_id_ = POINTS_ENTITY_ID;

  static bool is_texture_loaded_;
};
