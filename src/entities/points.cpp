#include "entities/points.h"

#include "collision_manager.h"
#include "hud.h"
#include "world.h"

void Points::DoLogic() {
  if (x_ < -w_) {
    health_ = 0;
  }

  x_ += dx_;
}

std::string Points::GetEntityId() { return entity_id_; }

bool Points::IsTextureLoaded() { return is_texture_loaded_; }

void Points::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
};

void Points::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == "PLYR") {
    --health_;
  }
};

EntitySharedPtr Points::Spawn(float x, float y, float dx, int h) {
  EntitySharedPtr entity = World::AddEntityToWorld<Points>(
      [x, y, dx]() { return std::make_shared<Points>(x, y, dx); });

  entity->y_ += (h / 2) - (entity->h_ / 2);

  return entity;
}

bool Points::is_texture_loaded_ = false;
