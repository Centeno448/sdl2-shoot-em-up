#pragma once

#include <SDL.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "sdl_wrappers.h"

struct Texture {
  Texture(std::string id, SDL_Texture* texture) : id_(id) {
    texture_.reset(texture, &SDLTextureDeleter);
  };

  std::string id_;
  SDLTextureSharedPtr texture_;
};

class TextureManager {
 private:
  inline static std::vector<Texture> loaded_textures_ = {};

  inline static SDLRendererSharedPtr renderer_ = nullptr;

 public:
  static SDL_Renderer* const GetRenderer();

  static void StaticInit(SDLRendererSharedPtr renderer);

  static SDLTextureSharedPtr LoadTexture(std::string id, std::string path);

  static SDLTextureSharedPtr GetTextureById(std::string id);

  static void UnloadTextureById(std::string id);
};
