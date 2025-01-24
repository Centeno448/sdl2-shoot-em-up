#pragma once

#include <forward_list>
#include <map>
#include <string>

#include "entity.h"

typedef std::map<std::string, std::forward_list<EntitySharedPtr>>
    CollisionLayerMap;

class CollisionManager {
 public:
  static CollisionLayerMap layers_;
};
