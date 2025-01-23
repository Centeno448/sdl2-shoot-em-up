#include "player.h"

#include <SDL.h>

#include "defs.h"
#include "input_manager.h"

void Player::DoLogic() {
  dy_ = dx_ = 0;

  if (InputManager::inputs_.at(SDL_SCANCODE_W)) {
    dy_ = -PLAYER_SPEED;
  }

  if (InputManager::inputs_.at(SDL_SCANCODE_S)) {
    dy_ = PLAYER_SPEED;
  }

  if (InputManager::inputs_.at(SDL_SCANCODE_A)) {
    dx_ = -PLAYER_SPEED;
  }

  if (InputManager::inputs_.at(SDL_SCANCODE_D)) {
    dx_ = PLAYER_SPEED;
  }

  x_ += dx_;
  y_ += dy_;
}
