#include <forward_list>

#include "entity.h"

class World {
 public:
  void InitWorld();

  std::forward_list<Entity> figthers_;
  std::forward_list<Entity> bullets_;
};
