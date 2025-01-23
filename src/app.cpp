#include "app.h"

#include <format>
#include <memory>

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

void App::Run() {
  PrepareScene();

  HandleInput();

  if (player_ != nullptr) {
    HandlePlayerMovement();
    player_->DrawTexture(GetRenderer());
  }

  for (Entity& e : entities_) {
    e.DrawTexture(GetRenderer());
  }

  PresentScene();

  SDL_Delay(16);  // ~60fps
}

SDL_Renderer* const App::GetRenderer() { return renderer_.get(); }

bool App::ShouldKeepRunning() { return should_keep_running_; }

bool App::RegisterEntity(int x, int y, const std::string path) {
  entities_.emplace_front(x, y);

  entities_.begin()->SetTexture(GetRenderer(), path);

  return true;
}

void App::RegisterPlayer(int x, int y) {
  player_.reset(new Entity(100, 100));
  player_->SetTexture(GetRenderer(), PLAYER_TEXTURE);
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

void App::HandleInput() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        should_keep_running_ = false;
        break;

      case SDL_KEYDOWN:
        HandleKeyDown(&event.key);
        break;

      case SDL_KEYUP:
        HandleKeyUp(&event.key);
        break;

      default:
        break;
    }
  }
}

void App::HandleKeyDown(SDL_KeyboardEvent* event) {
  if (event->repeat) {
    return;
  }

  if (event->keysym.scancode == SDL_SCANCODE_W) {
    up_ = true;
  }

  if (event->keysym.scancode == SDL_SCANCODE_A) {
    left_ = true;
  }

  if (event->keysym.scancode == SDL_SCANCODE_S) {
    down_ = true;
  }

  if (event->keysym.scancode == SDL_SCANCODE_D) {
    right_ = true;
  }
}

void App::HandleKeyUp(SDL_KeyboardEvent* event) {
  if (event->repeat) {
    return;
  }

  if (event->keysym.scancode == SDL_SCANCODE_W) {
    up_ = false;
  }

  if (event->keysym.scancode == SDL_SCANCODE_A) {
    left_ = false;
  }

  if (event->keysym.scancode == SDL_SCANCODE_S) {
    down_ = false;
  }

  if (event->keysym.scancode == SDL_SCANCODE_D) {
    right_ = false;
  }
}

void App::HandlePlayerMovement() {
  if (up_) {
    player_->y_ -= 4;
  }

  if (down_) {
    player_->y_ += 4;
  }

  if (left_) {
    player_->x_ -= 4;
  }

  if (right_) {
    player_->x_ += 4;
  }
}

void App::PrepareScene() {
  SDL_SetRenderDrawColor(renderer_.get(), 96, 128, 255, 255);
  SDL_RenderClear(renderer_.get());
}

void App::PresentScene() { SDL_RenderPresent(renderer_.get()); }
