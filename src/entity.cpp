#include "entity.h"

#include <SDL_image.h>

void Entity::Draw(SDL_Renderer* const renderer) {
  SDL_Rect dest;

  dest.x = x_;
  dest.y = y_;

  if (texture_ == nullptr) {
    std::string texture_id = GetTextureId();

    auto texture_from_manager = TextureManager::GetTextureById(texture_id);

    if (texture_from_manager == nullptr) {
      texture_ = TextureManager::LoadTextureById(renderer, texture_id);
    } else {
      texture_ = texture_from_manager;
    }

    SDL_QueryTexture(texture_.get(), NULL, NULL, &w_, &h_);
  }

  SDL_QueryTexture(texture_.get(), NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(renderer, texture_.get(), NULL, &dest);
}

std::string Entity::GetTextureId() { return std::string("IDK"); }

void Entity::DoLogic() {}

bool Entity::IsDead() { return health_ == 0; }
