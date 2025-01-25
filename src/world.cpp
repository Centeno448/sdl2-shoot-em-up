#include "world.h"

#include "algorithm"

std::forward_list<EntitySharedPtr> World::entities_ = {};

EntitySharedPtr World::GetEntityById(std::string id) {
  auto found =
      std::find_if(entities_.cbegin(), entities_.cend(),
                   [id](EntitySharedPtr e) { return e->GetTextureId() == id; });

  if (found != entities_.cend()) {
    return *found;
  }

  return nullptr;
}
