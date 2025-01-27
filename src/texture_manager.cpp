#include "texture_manager.h"

#include <SDL_image.h>

#include <algorithm>
#include <fmt/format.h>

#include "defs.h"
#include "log.h"

void TextureManager::StaticInit(SDLRendererSharedPtr renderer) {
  renderer_ = renderer;

  LoadTextureById(BACKGROUND_TEXTURE_ID);
  LoadTextureById(EXPLOSION_TEXTURE_ID);
  LoadTextureById(FONT_TEXTURE_ID);
}

SDLTextureSharedPtr TextureManager::GetTextureById(std::string id) {
  auto found =
      std::find_if(loaded_textures_.cbegin(), loaded_textures_.cend(),
                   [&id](Texture texture) { return texture.id_ == id; });

  if (found != loaded_textures_.cend()) {
    return found->texture_;
  }

  Log::Error(fmt::format("Failed to get texture {}. Texture not found", id));

  return nullptr;
}

SDLTextureSharedPtr TextureManager::LoadTextureById(std::string id) {
  if (!renderer_) {
    Log::Error(fmt::format(
        "Failed to load texture {}. No renderer set in TextureManager!", id));
    return nullptr;
  }

  std::string path = texture_map_.at(id);

  Log::Info(fmt::format("Loading texture {} with path {}", id, path));

  SDL_Texture* t = IMG_LoadTexture(GetRenderer(), path.c_str());

  loaded_textures_.emplace_back(id, t);

  return loaded_textures_.back().texture_;
}

SDL_Renderer* const TextureManager::GetRenderer() { return renderer_.get(); }

std::vector<Texture> TextureManager::loaded_textures_ = {};

std::map<std::string, std::string> TextureManager::texture_map_ = {
    {PLAYER_ENTITY_ID, PLAYER_TEXTURE},
    {BULLET_ENTITY_ID, BULLET_TEXTURE},
    {ENEMY_ENTITY_ID, ENEMY_TEXTURE},
    {ENEMY_BULLET_ENTITY_ID, ENEMY_BULLET_TEXTURE},
    {POINTS_ENTITY_ID, POINTS_TEXTURE},
    {BACKGROUND_TEXTURE_ID, BACKGROUND_TEXTURE},
    {EXPLOSION_TEXTURE_ID, EXPLOSION_TEXTURE},
    {FONT_TEXTURE_ID, FONT_TEXTURE}};

SDLRendererSharedPtr TextureManager::renderer_ = nullptr;
