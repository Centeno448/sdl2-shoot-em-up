#include "entity.h"

#include <SDL_image.h>

#include "log.h"

void Entity::Draw(SDL_Renderer* const renderer) {
  SDL_Rect dest;

  dest.x = x_;
  dest.y = y_;

  if (texture_ == nullptr) {
    Log::Error(std::format("Texture not set for {}", GetTextureId()));
    return;
  }

  SDL_QueryTexture(texture_.get(), NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(renderer, texture_.get(), NULL, &dest);
}

std::string Entity::GetTextureId() { return std::string("IDK"); }

void Entity::DoLogic() {}

bool Entity::IsDead() { return health_ == 0; }

bool Entity::IsTextureLoaded() { return true; }

void Entity::SetTextureLoaded(bool is_loaded) {}

std::string Entity::GetCollisionLayer() { return std::string(); }

void Entity::HandleCollision(EntitySharedPtr collied_with) {}
