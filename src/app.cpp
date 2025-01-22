#include "app.h"

#include <format>

#include "defs.h"
#include "string_utils.h"

void SDLRendererDeleter(SDL_Renderer* renderer) {
  SDL_DestroyRenderer(renderer);
}

void SDLWindowDeleter(SDL_Window* window) { SDL_DestroyWindow(window); }

App::~App() {
  renderer_.reset();
  window_.reset();
  SDL_Quit();
}

bool App::ShouldKeepRunning() { return should_keep_running_; }

bool App::Init() {
  int renderer_flags = SDL_RENDERER_ACCELERATED;
  int window_flags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    StringUtils::LogError(
        std::format("Failed to initialize SDL with error: {}", SDL_GetError()));
    return false;
  }

  window_.reset(SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                 SCREEN_HEIGHT, window_flags));

  if (!window_) {
    StringUtils::LogError(std::format(
        "Failed to create SDL window with error: {}", SDL_GetError()));
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  renderer_.reset(SDL_CreateRenderer(window_.get(), -1, renderer_flags));

  if (!renderer_) {
    StringUtils::LogError(std::format(
        "Failed to create SDL renderer with error: {}", SDL_GetError()));
    return false;
  }

  return true;
}

void App::HandleInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        should_keep_running_ = false;
        break;

      default:
        break;
    }
  }
}

void App::PrepareScene() {
  SDL_SetRenderDrawColor(renderer_.get(), 96, 128, 255, 255);
  SDL_RenderClear(renderer_.get());
}

void App::PresentScene() { SDL_RenderPresent(renderer_.get()); }

void App::Run() {
  PrepareScene();

  HandleInput();

  PresentScene();

  SDL_Delay(16);
}
