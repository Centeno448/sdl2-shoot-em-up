#include "texture_manager.h"

#include <SDL_image.h>

#include <algorithm>
#include <format>

#include "defs.h"
#include "log.h"

void SDLTextureDeleter(SDL_Texture* texture) { SDL_DestroyTexture(texture); }

SDLTextureSharedPtr TextureManager::GetTextureById(std::string id) {
  auto found =
      std::find_if(loaded_textures_.cbegin(), loaded_textures_.cend(),
                   [&id](Texture texture) { return texture.id_ == id; });

  if (found != loaded_textures_.cend()) {
    return found->texture_;
  }

  return nullptr;
}

SDLTextureSharedPtr TextureManager::LoadTextureById(
    SDL_Renderer* const renderer, std::string id) {
  std::string path = texture_map_.at(id);

  Log::Info(std::format("Loading texture {} with path {}", id, path));

  SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
  loaded_textures_.emplace_back(id, texture);
  return GetTextureById(id);
}

std::vector<Texture> TextureManager::loaded_textures_ = {};

std::map<std::string, std::string> TextureManager::texture_map_ = {
    {PLAYER_TEXTURE_ID, PLAYER_TEXTURE}, {BULLET_TEXTURE_ID, BULLET_TEXTURE}};
