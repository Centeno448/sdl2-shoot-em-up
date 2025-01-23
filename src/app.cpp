#include "app.h"

#include <SDL_image.h>

#include <format>
#include <memory>

#include "defs.h"
#include "input_manager.h"
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

void App::Run() {
  PrepareScene();

  HandleEvents();

  DoLogic();

  PresentScene();

  SDL_Delay(16);  // ~60fps
}

SDL_Renderer* const App::GetRenderer() { return renderer_.get(); }

bool App::ShouldKeepRunning() { return should_keep_running_; }

void App::RegisterEntity(int x, int y, const std::string path) {
  // entities_.emplace_front(x, y);

  // entities_.begin()->SetTexture(GetRenderer(), path);

  // return true;
}

void App::RegisterPlayer(int x, int y) {
  player_.reset(new Player(100, 100));

  player_->SetTexture(IMG_LoadTexture(GetRenderer(), PLAYER_TEXTURE));
}

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

  RegisterPlayer(100, 100);

  return true;
}

void App::HandleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        should_keep_running_ = false;
        break;

      case SDL_KEYDOWN:
        InputManager::HandleKeyDown(&event.key);
        break;

      case SDL_KEYUP:
        InputManager::HandleKeyUp(&event.key);
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

void App::DoLogic() {
  if (player_ != nullptr) {
    player_->DoLogic();
    player_->Draw(GetRenderer());
  }

  // for (Entity& e : entities_) {
  //   e.Draw(GetRenderer());
  // }
}
