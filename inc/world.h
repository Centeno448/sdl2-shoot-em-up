#pragma once

#include <forward_list>

#include "entity.h"

class World {
 public:
  static EntitySharedPtr GetEntityById(std::string id);

  static void ResetWorld();

  static void StaticInit(SDLRendererSharedPtr renderer);

  static void InitialState();

  static void UpdateWorld();

  static void DrawWorld();

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

  // Load texture if we haven't already
  if (!shared_entity->IsTextureLoaded()) {
    SDLTextureSharedPtr texture =
        TextureManager::LoadTextureById(shared_entity->GetEntityId());

    if (texture == nullptr) {
      return nullptr;
    }

    shared_entity->texture_ = texture;
    shared_entity->SetTextureLoaded(true);
  } else {
    SDLTextureSharedPtr texture =
        TextureManager::GetTextureById(shared_entity->GetEntityId());
    shared_entity->texture_ = texture;
  }

  SDL_QueryTexture(shared_entity->texture_.get(), NULL, NULL,
                   &shared_entity->w_, &shared_entity->h_);

  entities_.emplace_front(shared_entity);

  return shared_entity;
}
