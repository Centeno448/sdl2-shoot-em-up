#include "texture_manager.h"

#include <SDL_image.h>

#include <algorithm>
#include <format>

#include "defs.h"
#include "log.h"

void TextureManager::StaticInit(SDLRendererSharedPtr renderer) {
  renderer_ = renderer;
}

SDLTextureSharedPtr TextureManager::GetTextureById(std::string id) {
  auto found =
      std::find_if(loaded_textures_.cbegin(), loaded_textures_.cend(),
                   [&id](Texture texture) { return texture.id_ == id; });

  if (found != loaded_textures_.cend()) {
    return found->texture_;
  }

  Log::Error(std::format("Failed to get texture {}. Texture not found", id));

  return nullptr;
}

SDLTextureSharedPtr TextureManager::LoadTextureById(std::string id) {
  if (!renderer_) {
    Log::Error(std::format(
        "Failed to load texture {}. No renderer set in TextureManager!", id));
    return nullptr;
  }

  std::string path = texture_map_.at(id);

  Log::Info(std::format("Loading texture {} with path {}", id, path));

  SDL_Texture* t = IMG_LoadTexture(GetRenderer(), path.c_str());

  loaded_textures_.emplace_back(id, t);

  return loaded_textures_.back().texture_;
}

SDL_Renderer* const TextureManager::GetRenderer() { return renderer_.get(); }

std::vector<Texture> TextureManager::loaded_textures_ = {};

std::map<std::string, std::string> TextureManager::texture_map_ = {
    {PLAYER_TEXTURE_ID, PLAYER_TEXTURE},
    {BULLET_TEXTURE_ID, BULLET_TEXTURE},
    {ENEMY_TEXTURE_ID, ENEMY_TEXTURE},
    {ENEMY_BULLET_TEXTURE_ID, ENEMY_BULLET_TEXTURE}};

SDLRendererSharedPtr TextureManager::renderer_ = nullptr;
