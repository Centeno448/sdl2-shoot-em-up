#pragma once

#include <SDL.h>

#include <map>

typedef std::map<SDL_Scancode, bool> InputMap;

class InputManager {
 public:
  static InputMap inputs_;

  static void HandleKeyDown(SDL_KeyboardEvent* event);
  static void HandleKeyUp(SDL_KeyboardEvent* event);
};
