#include "entities/player.h"

#include <SDL.h>

#include "collision_manager.h"
#include "defs.h"
#include "entities/bullet.h"
#include "input_manager.h"
#include "log.h"
#include "sound_manager.h"
#include "world.h"

void Player::DoLogic() {
  dy_ = dx_ = 0;

  if (reload_frames_ > 0) {
    --reload_frames_;
  }

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

  if (InputManager::inputs_.at(SDL_SCANCODE_SPACE) && reload_frames_ == 0) {
    Shoot();
  }

  x_ += dx_;
  y_ += dy_;
}

void Player::Shoot() {
  // Spawn bullet
  EntitySharedPtr bullet = World::AddEntityToWorld<Bullet>(
      [this]() { return std::make_shared<Bullet>(x_ + (h_ / 2), y_); });

  // TODO: Stop app on failure to spawn bullet

  bullet->y_ += (h_ / 2) - (bullet->h_ / 2);

  // Set firing cooldown
  reload_frames_ = 8;

  SoundManager::PlaySoundById(PLAYER_SHOT_SFX_ID, SoundChannel::CH_PLAYER);
}

void Player::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == "ENMY_BLLT") {
    --health_;
  }
};

std::string Player::GetEntityId() { return texture_id_; }

bool Player::IsTextureLoaded() { return is_texture_loaded_; }

void Player::SetTextureLoaded(bool is_loaded) {
  is_texture_loaded_ = is_loaded;
}

bool Player::is_texture_loaded_ = false;

void Player::OnDeath() {
  SoundManager::PlaySoundById(PLAYER_DEATH_SFX_ID, SoundChannel::CH_PLAYER);
  World::ResetWorld();
}

void Player::RegisterPlayer() {
  float x = 100, y = 100;
  EntitySharedPtr entity = World::AddEntityToWorld<Player>(
      [x, y]() { return std::make_shared<Player>(x, y); });

  CollisionManager::layers_.at(ENEMY_BULLET_ENTITY_ID).push_front(entity);
}
