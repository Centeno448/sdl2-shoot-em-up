#pragma once

#include "defs.h"
#include "entity.h"

class Player : public Entity {
 public:
  Player(float x, float y) : Entity(x, y) { health_ = 3; };
  int reload_frames_ = 0;

  void DoLogic() override;

  std::string GetEntityId() override;

  void HandleCollision(EntitySharedPtr collided_with) override;

  void OnDeath() override;

  void ConfigureEntity();

  static void RegisterPlayer();

 private:
  inline static const std::string entity_id_ = PLAYER_ENTITY_ID;

  inline static bool is_texture_loaded_ = false;

  void Shoot();

  void SpawnExplosion();

  void SpawnDebris();

  void ConfigureTexture();
};
