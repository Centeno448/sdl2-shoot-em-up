#pragma once

#include <SDL.h>

#include <forward_list>
#include <memory>

#include "defs.h"
#include "entities/entity.h"
#include "sdl_wrappers.h"

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

  SDL_Renderer* const GetRenderer();

  bool ShouldKeepRunning();

  static void StopApp(std::string reason);

  static bool unrecoverable_;

 private:
  void Init();

  bool InitSDL();

  void HandleEvents();

  void PrepareScene();

  void DoLogic();

  void DrawScene();

  void PresentScene();

  SDLRendererSharedPtr renderer_;
  SDLWindowUniquePtr window_;
  static bool should_keep_running_;
};
