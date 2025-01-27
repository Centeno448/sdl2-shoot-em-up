#include "input_manager.h"

#include "defs.h"
#include "log.h"

bool InputManager::IsKeyPressed(SDL_Scancode key_code) {
  if (!inputs_.contains(key_code)) {
    inputs_[key_code] = false;
  }

  return inputs_.at(key_code);
}

void InputManager::SetKeyPressed(SDL_Scancode key_code, bool value) {
  if (!inputs_.contains(key_code)) {
    inputs_[key_code];
  }

  inputs_.at(key_code) = value;
}

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

  SDL_Scancode key_code = event->keysym.scancode;

  if (key_code > MAX_KEYBOARD_KEYS) {
    return;
  }

  inputs_[key_code] = false;
}

InputMap InputManager::inputs_ = {{SDL_SCANCODE_W, false},
                                  {SDL_SCANCODE_A, false},
                                  {SDL_SCANCODE_S, false},
                                  {SDL_SCANCODE_D, false},
                                  {SDL_SCANCODE_SPACE, false}};
