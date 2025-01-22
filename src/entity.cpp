#include "entity.h"

#include <SDL_image.h>

#include <format>

#include "string_utils.h"

void SDLTextureDeleter(SDL_Texture* texture) { SDL_DestroyTexture(texture); }

bool Entity::SetTexture(const std::string path) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", path);

  texture_.reset(IMG_LoadTexture(app_.renderer_.get(), path.c_str()));

  if (!texture_) {
    StringUtils::LogError(std::format("Failed to load texture {}", path));
    return false;
  }

  return true;
}

void Entity::DrawTexture() {
  SDL_Rect dest;

  dest.x = x_;
  dest.y = y_;

  SDL_QueryTexture(texture_.get(), NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(app_.renderer_.get(), texture_.get(), NULL, &dest);
}
