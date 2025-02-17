#pragma once

#include <SDL.h>

#include <forward_list>
#include <memory>
#include <string>

#include "defs.h"
#include "scenes/scene.h"
#include "sdl_wrappers.h"

class App {
 public:
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

  void PresentScene();

  SDLRendererSharedPtr renderer_;

  SDLWindowUniquePtr window_;
  static bool should_keep_running_;
};
