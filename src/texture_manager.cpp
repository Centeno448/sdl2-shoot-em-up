#include "texture_manager.h"

#include <SDL_image.h>
#include <fmt/format.h>

#include <algorithm>

#include "defs.h"
#include "log.h"

void TextureManager::StaticInit(SDLRendererSharedPtr renderer) {
  renderer_ = renderer;

  LoadTexture(BACKGROUND_TEXTURE_ID, BACKGROUND_TEXTURE);

  LoadTexture(FONT_TEXTURE_ID, FONT_TEXTURE);
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

SDLTextureSharedPtr TextureManager::LoadTexture(std::string id,
                                                std::string path) {
  if (!renderer_) {
    Log::Error(fmt::format(
        "Failed to load texture {}. No renderer set in TextureManager!", id));
    return nullptr;
  }

  Log::Info(fmt::format("Loading texture {} with path {}", id, path));

  SDL_Texture* t = IMG_LoadTexture(GetRenderer(), path.c_str());

  loaded_textures_.emplace_back(id, t);

  return loaded_textures_.back().texture_;
}

void TextureManager::UnloadTextureById(std::string id) {
  auto found =
      std::find_if(loaded_textures_.cbegin(), loaded_textures_.cend(),
                   [&id](Texture texture) { return texture.id_ == id; });

  if (found != loaded_textures_.cend()) {
    loaded_textures_.erase(found);
  }
}

SDL_Renderer* const TextureManager::GetRenderer() { return renderer_.get(); }
