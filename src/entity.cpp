#include "entity.h"

#include <SDL_image.h>

#include <format>

#include "string_utils.h"

void SDLTextureDeleter(SDL_Texture* texture) { SDL_DestroyTexture(texture); }

void Entity::SetTexture(SDL_Texture* texture) {
  texture_.reset(texture, &SDLTextureDeleter);
}

void Entity::Draw(SDL_Renderer* const renderer) {
  SDL_Rect dest;

  dest.x = x_;
  dest.y = y_;

  SDL_QueryTexture(texture_.get(), NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(renderer, texture_.get(), NULL, &dest);
}

void Entity::DoLogic() {}
