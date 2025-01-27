#pragma once

#include <SDL.h>

#include <map>

typedef std::map<SDL_Scancode, bool> InputMap;

class InputManager {
 public:
  static bool IsKeyPressed(SDL_Scancode key_code);
  static void SetKeyPressed(SDL_Scancode key_code, bool value);
  static void HandleKeyDown(SDL_KeyboardEvent* event);
  static void HandleKeyUp(SDL_KeyboardEvent* event);

 private:
  static InputMap inputs_;
};
