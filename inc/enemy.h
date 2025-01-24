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

  static void RegisterEnemy();

 private:
  inline static const std::string texture_id_ = ENEMY_TEXTURE_ID;

  static bool is_texture_loaded_;
};
