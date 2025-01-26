#include "entities/player.h"

#include <SDL.h>

#include "collision_manager.h"
#include "defs.h"
#include "effects/debris.h"
#include "effects/effect_manager.h"
#include "effects/explosion.h"
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
    SoundManager::PlaySoundById(PLAYER_HIT_SFX_ID, SoundChannel::CH_PLAYER);
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
  SpawnExplosion();
  SpawnDebris();
  World::ResetWorld();
}

void Player::RegisterPlayer() {
  float x = 100, y = 100;
  EntitySharedPtr entity = World::AddEntityToWorld<Player>(
      [x, y]() { return std::make_shared<Player>(x, y); });

  CollisionManager::layers_.at(ENEMY_BULLET_ENTITY_ID).push_front(entity);
}

void Player::SpawnExplosion() {
  const int k_explosion_layers = 20;
  for (int i = 0; i < k_explosion_layers; ++i) {
    EffectManager::AddEffect<Explosion>(
        [this]() { return std::make_shared<Explosion>(x_, y_); }, 1);
  }
}

void Player::SpawnDebris() {
  int w = w_ / 2;
  int h = h_ / 2;

  SDL_Rect source;

  source.x = static_cast<int>(x_);
  source.y = static_cast<int>(y_);
  source.w = static_cast<int>(w_);
  source.h = static_cast<int>(h_);

  for (int y = 0; y <= h; y += h) {
    for (int x = 0; x <= w; x += w) {
      SDL_Rect debris_shard;

      debris_shard.x = x;
      debris_shard.y = y;
      debris_shard.w = w;
      debris_shard.h = h;
      EffectManager::AddEffect<Debris>(
          [this, source, debris_shard]() {
            return std::make_shared<Debris>(source, debris_shard, texture_);
          },
          1);
    }
  }
}
