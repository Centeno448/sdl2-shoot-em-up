#include "input_manager.h"

#include "defs.h"
#include "string_utils.h"

void InputManager::HandleKeyDown(SDL_KeyboardEvent* event) {
  if (event->repeat) {
    return;
  }

  SDL_Scancode key_code = event->keysym.scancode;

  if (key_code > MAX_KEYBOARD_KEYS) {
    return;
  }

  inputs_[key_code] = true;
}

void InputManager::HandleKeyUp(SDL_KeyboardEvent* event) {
  if (event->repeat) {
    return;
  }

  if (event->keysym.scancode > MAX_KEYBOARD_KEYS) {
    return;
  }

  inputs_[event->keysym.scancode] = false;
}

InputMap InputManager::inputs_ = {
    {SDL_SCANCODE_W, false},
    {SDL_SCANCODE_A, false},
    {SDL_SCANCODE_S, false},
    {SDL_SCANCODE_D, false},
};
