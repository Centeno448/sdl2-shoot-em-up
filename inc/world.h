#include <forward_list>

#include "entity.h"

class World {
 public:
  static std::forward_list<EntitySharedPtr> entities_;
  template <typename T, typename F>
  static EntitySharedPtr AddEntityToWorld(F f);
};

template <typename T, typename F>
EntitySharedPtr World::AddEntityToWorld(F f) {
  std::shared_ptr<T> shared_t = f();

  EntitySharedPtr shared_entity = std::static_pointer_cast<Entity>(shared_t);

  entities_.emplace_front(shared_entity);

  return shared_entity;
}
