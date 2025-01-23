#include "texture_manager.h"

#include <SDL_image.h>

#include <algorithm>

#include "defs.h"

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

void TextureManager::LoadTextureById(SDL_Renderer* const renderer,
                                     std::string id) {
  std::string path = texture_map_.at(id);
  SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
  loaded_textures_.emplace_back(id, texture);
}

std::vector<Texture> TextureManager::loaded_textures_ = {};

std::map<std::string, std::string> TextureManager::texture_map_ = {
    {"PLYR", PLAYER_TEXTURE}, {"BLLT", BULLET_TEXTURE}};
