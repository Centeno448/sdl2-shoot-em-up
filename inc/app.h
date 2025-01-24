#pragma once

#include <SDL.h>

#include <forward_list>
#include <memory>

#include "defs.h"
#include "entity.h"
#include "sdl_wrappers.h"

class TimerCallback {
 public:
  TimerCallback(int frequency, bool one_off, void (*const callback)())
      : frequency_(frequency),
        frames_until_(frequency),
        one_off_(one_off),
        callback_(callback) {
    id_ = next_id_;
    ++next_id_;
  };

  int frames_until_;
  const int frequency_;
  const bool one_off_;
  void (*const callback_)();

  friend bool operator==(const TimerCallback& lhs, const TimerCallback& rhs);

 private:
  int id_;
  static int next_id_;
};

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

  void RegisterPlayer(float x, float y);

  static void StopApp(std::string reason);

  static bool unrecoverable_;

  static void RegisterTimerCallback(int frequency, bool one_off,
                                    void (*const callback)());

 private:
  bool Init();

  void HandleEvents();

  void PrepareScene();

  void DoLogic();

  void DrawScene();

  void PresentScene();

  SDLRendererSharedPtr renderer_;
  SDLWindowUniquePtr window_;
  static bool should_keep_running_;
  static std::forward_list<TimerCallback> timer_callbacks_;
};
