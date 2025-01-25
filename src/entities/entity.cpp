#include "entities/entity.h"

#include <SDL_image.h>

#include "log.h"

void Entity::Draw(SDL_Renderer* const renderer) {
  SDL_Rect dest;

  dest.x = static_cast<int>(x_);
  dest.y = static_cast<int>(y_);

  if (texture_ == nullptr) {
    Log::Error(std::format("Texture not set for {}", GetEntityId()));
    return;
  }

  SDL_QueryTexture(texture_.get(), NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(renderer, texture_.get(), NULL, &dest);
}

std::string Entity::GetEntityId() { return std::string("IDK"); }

void Entity::DoLogic() {}

bool Entity::IsDead() { return health_ == 0; }

bool Entity::IsTextureLoaded() { return true; }

void Entity::SetTextureLoaded(bool is_loaded) {}

std::string Entity::GetCollisionLayer() { return std::string(); }

void Entity::HandleCollision(EntitySharedPtr collied_with) {}

void Entity::OnDeath() {}
