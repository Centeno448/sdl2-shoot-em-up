#include "collision_manager.h"

#include <math.h>

#include "defs.h"

CollisionLayerMap CollisionManager::layers_ = {{BULLET_ENTITY_ID, {}},
                                               {ENEMY_BULLET_ENTITY_ID, {}},
                                               {POINTS_ENTITY_ID, {}}};

void CollisionManager::CheckCollision(EntitySharedPtr entity) {
  auto entity_class_id = entity->GetEntityId();

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
  float x1 = lhs->x_, y1 = lhs->y_, w1 = static_cast<float>(lhs->w_),
        h1 = static_cast<float>(lhs->h_);

  float x2 = rhs->x_, y2 = rhs->y_, w2 = static_cast<float>(rhs->w_),
        h2 = static_cast<float>(rhs->h_);

  return (std::max(x1, x2) < std::min(x1 + w1, x2 + w2)) &&
         (std::max(y1, y2) < std::min(y1 + h1, y2 + h2));
}

void CollisionManager::ClearLayers() {
  for (auto &t : layers_) {
    t.second.clear();
  }
}

void CollisionManager::AddEntityToLayer(std::string layer_id,
                                        EntitySharedPtr entity) {
  layers_.at(layer_id).push_front(entity);
}

void CollisionManager::RemoveEntityFromLayer(std::string layer_id,
                                             EntitySharedPtr entity) {
  layers_.at(layer_id).remove(entity);
}
