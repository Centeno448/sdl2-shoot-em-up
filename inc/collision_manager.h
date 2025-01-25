#pragma once

#include <forward_list>
#include <map>
#include <string>

#include "entities/entity.h"

typedef std::map<std::string, std::forward_list<EntitySharedPtr>>
    CollisionLayerMap;

class CollisionManager {
 public:
  static CollisionLayerMap layers_;

  static void CheckCollision(EntitySharedPtr entity);

 private:
  static bool DetermineCollision(EntitySharedPtr lhs, EntitySharedPtr rhs);
};
