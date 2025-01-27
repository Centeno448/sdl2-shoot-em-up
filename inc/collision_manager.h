#pragma once

#include <forward_list>
#include <map>
#include <string>

#include "entities/entity.h"

typedef std::map<std::string, std::forward_list<EntitySharedPtr>>
    CollisionLayerMap;

class CollisionManager {
 public:
  static void ClearLayers();

  static void AddEntityToLayer(std::string layer_id, EntitySharedPtr entity);

  static void RemoveEntityFromLayer(std::string layer_id,
                                    EntitySharedPtr entity);

  static void CheckCollision(EntitySharedPtr entity);

 private:
  static CollisionLayerMap layers_;
  static bool DetermineCollision(EntitySharedPtr lhs, EntitySharedPtr rhs);
};
