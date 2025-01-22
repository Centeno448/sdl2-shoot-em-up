#pragma once

#include <SDL.h>

#include <forward_list>
#include <memory>

#include "entity.h"

void SDLRendererDeleter(SDL_Renderer* renderer);

void SDLWindowDeleter(SDL_Window* window);

typedef std::unique_ptr<SDL_Renderer, decltype(&SDLRendererDeleter)>
    SDLRendererUniquePtr;
typedef std::unique_ptr<SDL_Window, decltype(&SDLWindowDeleter)>
    SDLWindowUniquePtr;

class App {
 public:
  friend class Entity;
  App()
      : renderer_(nullptr, &SDLRendererDeleter),
        window_(nullptr, &SDLWindowDeleter) {
    Init();
  };

  ~App();

  void Run();

  SDL_Renderer* GetRenderer();

  bool ShouldKeepRunning();

  bool RegisterEntity(int x, int y, const std::string path);

 private:
  bool Init();

  void HandleInput();

  void PrepareScene();

  void PresentScene();

  SDLRendererUniquePtr renderer_;
  SDLWindowUniquePtr window_;
  std::forward_list<Entity> entities_;
  bool should_keep_running_;
};
