#include "collision_manager.h"

#include <math.h>

#include "defs.h"

CollisionLayerMap CollisionManager::layers_ = {{BULLET_TEXTURE_ID, {}},
                                               {ENEMY_BULLET_TEXTURE_ID, {}}};

void CollisionManager::CheckCollision(EntitySharedPtr entity) {
  auto entity_class_id = entity->GetTextureId();

  if (!layers_.contains(entity_class_id)) {
    return;
  }

  for (auto &collides_with : layers_.at(entity_class_id)) {
    if (DetermineCollision(entity, collides_with)) {
      entity->HandleCollision(collides_with);
      collides_with->HandleCollision(entity);
    }
  }
}

bool CollisionManager::DetermineCollision(EntitySharedPtr lhs,
                                          EntitySharedPtr rhs) {
  int x1 = lhs->x_, y1 = lhs->y_, w1 = lhs->w_, h1 = lhs->h_;

  int x2 = rhs->x_, y2 = rhs->y_, w2 = rhs->w_, h2 = rhs->h_;

  return (std::max(x1, x2) < std::min(x1 + w1, x2 + w2)) &&
         (std::max(y1, y2) < std::min(y1 + h1, y2 + h2));
}
