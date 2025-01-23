#include <SDL.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

void SDLTextureDeleter(SDL_Texture* texture);

typedef std::shared_ptr<SDL_Texture> SDLTextureSharedPtr;

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

  static void LoadTextureById(SDL_Renderer* const renderer, std::string id);

 public:
  static SDLTextureSharedPtr GetTextureById(std::string id);
};
