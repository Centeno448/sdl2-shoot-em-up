#include "player.h"

#include <SDL.h>

#include "bullet.h"
#include "defs.h"
#include "input_manager.h"
#include "world.h"

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

  if (InputManager::inputs_.at(SDL_SCANCODE_K)) {
    --health_;
  }

  if (InputManager::inputs_.at(SDL_SCANCODE_SPACE)) {
    Shoot();
  }

  x_ += dx_;
  y_ += dy_;
}

void Player::Shoot() {
  auto shared_bullet = std::make_shared<Bullet>(x_, y_);
  World::entities_.emplace_front(
      std::static_pointer_cast<Entity>(shared_bullet));
}

std::string Player::GetTextureId() { return texture_id_; }
