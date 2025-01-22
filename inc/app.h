#pragma once

#include <SDL.h>

#include <memory>

void SDLRendererDeleter(SDL_Renderer* renderer);

void SDLWindowDeleter(SDL_Window* window);

typedef std::unique_ptr<SDL_Renderer, decltype(&SDLRendererDeleter)>
    SDLRendererUniquePtr;
typedef std::unique_ptr<SDL_Window, decltype(&SDLWindowDeleter)>
    SDLWindowUniquePtr;

class App {
 public:
  App()
      : renderer_(nullptr, &SDLRendererDeleter),
        window_(nullptr, &SDLWindowDeleter) {
    Init();
  };

  ~App();

  void Run();

  bool ShouldKeepRunning();

 private:
  bool Init();

  void HandleInput();

  void PrepareScene();

  void PresentScene();

  SDLRendererUniquePtr renderer_;
  SDLWindowUniquePtr window_;
  bool should_keep_running_;
};
