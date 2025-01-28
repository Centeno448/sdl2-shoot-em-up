#pragma once

#include <forward_list>

#include "entities/entity.h"

class World {
 public:
  static EntitySharedPtr GetEntityById(std::string id);

  static void ResetWorld();

  static void StaticInit(SDLRendererSharedPtr renderer);

  static void InitialState();

  static void UpdateWorld();

  static void DrawWorld();

  static void ClearEntitiesNextTick();
  static void ClearEntitiesNow();

  template <typename T, typename F>
  static EntitySharedPtr AddEntityToWorld(F f);

 private:
  static std::forward_list<EntitySharedPtr> entities_;
  static SDL_Renderer* const GetRenderer();
  inline static SDLRendererSharedPtr renderer_ = nullptr;
};

template <typename T, typename F>
EntitySharedPtr World::AddEntityToWorld(F f) {
  std::shared_ptr<T> shared_t = f();

  EntitySharedPtr shared_entity = std::static_pointer_cast<Entity>(shared_t);

  shared_entity->ConfigureEntity();

  entities_.emplace_front(shared_entity);

  return shared_entity;
}
