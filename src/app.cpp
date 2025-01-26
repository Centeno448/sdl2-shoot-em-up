#include "app.h"

#include <SDL_image.h>
#include <SDL_mixer.h>

#include <format>
#include <memory>

#include "defs.h"
#include "effects/effect_manager.h"
#include "input_manager.h"
#include "log.h"
#include "sdl_wrappers.h"
#include "sound_manager.h"
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

void App::Init() {
  if (!InitSDL()) {
    StopApp("Failed to initialize SDL. See error output above.");
    return;
  }

  SoundManager::StaticInit();
  TextureManager::StaticInit(renderer_);
  EffectManager::StaticInit(renderer_);
  World::StaticInit(renderer_);

  World::InitialState();
}

bool App::InitSDL() {
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

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    Log::Error(std::format("Failed to initialize SDL mixer with error: {}",
                           SDL_GetError()));
    return false;
  }

  Mix_AllocateChannels(MAX_SOUND_CHANNELS);

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
  EffectManager::UpdateEffects();

  TimerManager::ProcessTimers();

  World::UpdateWorld();
}

void App::DrawScene() {
  EffectManager::DrawEffects();

  World::DrawWorld();
}

void App::StopApp(std::string error) {
  Log::Error(std::format("Stopping app due to unrecoverable error: {}", error));
  unrecoverable_ = true;
  should_keep_running_ = false;
}

bool App::unrecoverable_ = false;

bool App::should_keep_running_ = true;
