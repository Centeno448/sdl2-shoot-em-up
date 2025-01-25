#include "app.h"

#include <SDL_image.h>

#include <format>
#include <memory>

#include "collision_manager.h"
#include "defs.h"
#include "enemy.h"
#include "input_manager.h"
#include "log.h"
#include "player.h"
#include "sdl_wrappers.h"
#include "timer_manager.h"
#include "world.h"

App::~App() {
  renderer_.reset();
  window_.reset();
  SDL_Quit();
}

void App::Run() {
  PrepareScene();

  HandleEvents();

  DoLogic();

  DrawScene();

  PresentScene();

  SDL_Delay(16);  // ~60fps
}

SDL_Renderer* const App::GetRenderer() { return renderer_.get(); }

bool App::ShouldKeepRunning() { return should_keep_running_; }

bool App::Init() {
  int renderer_flags = SDL_RENDERER_ACCELERATED;
  int window_flags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    Log::Error(
        std::format("Failed to initialize SDL with error: {}", SDL_GetError()));
    return false;
  }

  window_.reset(SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                 SCREEN_HEIGHT, window_flags));

  if (!window_) {
    Log::Error(std::format("Failed to create SDL window with error: {}",
                           SDL_GetError()));
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  renderer_.reset(SDL_CreateRenderer(window_.get(), -1, renderer_flags),
                  &SDLRendererDeleter);

  if (!renderer_) {
    Log::Error(std::format("Failed to create SDL renderer with error: {}",
                           SDL_GetError()));
    return false;
  }

  TextureManager::StaticInit(renderer_);

  TimerManager::RegisterTimerCallback(0, true, &Player::RegisterPlayer);

  TimerManager::RegisterTimerCallback(60, false, &Enemy::RegisterEnemy);

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
  auto current_timer = TimerManager::timer_callbacks_.begin();
  while (current_timer != TimerManager::timer_callbacks_.end()) {
    if (current_timer->frames_until_ == 0) {
      current_timer->callback_();

      if (current_timer->one_off_) {
        auto to_delete = (*current_timer);
        ++current_timer;
        TimerManager::timer_callbacks_.remove(to_delete);
      } else {
        current_timer->frames_until_ = current_timer->frequency_;
        ++current_timer;
      }

    } else {
      --current_timer->frames_until_;
      ++current_timer;
    }
  }

  auto current_entity = World::entities_.begin();
  while (current_entity != World::entities_.end()) {
    if ((*current_entity)->IsDead()) {
      EntitySharedPtr to_delete = (*current_entity);
      ++current_entity;
      World::entities_.remove(to_delete);
      std::string collision_layer = to_delete->GetCollisionLayer();
      if (collision_layer.size()) {
        CollisionManager::layers_.at(collision_layer).remove(to_delete);
      }
    } else {
      (*current_entity)->DoLogic();
      CollisionManager::CheckCollision(*current_entity);
      ++current_entity;
    }
  }
}

void App::DrawScene() {
  for (EntitySharedPtr e : World::entities_) {
    e->Draw(GetRenderer());
  }
}

void App::StopApp(std::string error) {
  Log::Error(std::format("Stopping app due to unrecoverable error: {}", error));
  unrecoverable_ = true;
  should_keep_running_ = false;
}

bool App::unrecoverable_ = false;

bool App::should_keep_running_ = true;
