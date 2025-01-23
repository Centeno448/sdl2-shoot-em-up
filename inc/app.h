#pragma once

#include <SDL.h>

#include <forward_list>
#include <memory>

#include "defs.h"
#include "entity.h"
#include "player.h"

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
        window_(nullptr, &SDLWindowDeleter),
        should_keep_running_(true) {
    Init();
  };

  ~App();

  void Run();

  SDL_Renderer* const GetRenderer();

  bool ShouldKeepRunning();

  void RegisterPlayer(float x, float y);

 private:
  bool Init();

  void HandleEvents();

  void PrepareScene();

  void DoLogic();

  void DrawScene();

  void PresentScene();

  SDLRendererUniquePtr renderer_;
  SDLWindowUniquePtr window_;
  bool should_keep_running_;
};
