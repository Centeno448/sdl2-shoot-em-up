#include <forward_list>

#include "entity.h"

class World {
 public:
  static std::forward_list<EntitySharedPtr> entities_;
};
