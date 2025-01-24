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
  static std::vector<Texture> loaded_textures_;

  static std::map<std::string, std::string> texture_map_;

  static SDLRendererSharedPtr renderer_;

 public:
  static SDL_Renderer* const GetRenderer();

  static void StaticInit(SDLRendererSharedPtr renderer);

  static SDLTextureSharedPtr LoadTextureById(std::string id);

  static SDLTextureSharedPtr GetTextureById(std::string id);
};
