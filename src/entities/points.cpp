#include "entities/points.h"

#include "collision_manager.h"
#include "hud.h"
#include "sound_manager.h"
#include "world.h"

void Points::DoLogic() {
  if (x_ < -w_) {
    health_ = 0;
  }

  if (y_ > SCREEN_HEIGHT || y_ < 0) {
    dy_ *= -1;
  }

  --health_;

  x_ += dx_;
  y_ += dy_;
}

std::string Points::GetEntityId() { return entity_id_; }

void Points::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == PLAYER_ENTITY_ID) {
    --health_ = 0;
    SoundManager::PlaySoundById(POINTS_SFX_ID, SoundChannel::CH_POINTS);
  }
};

EntitySharedPtr Points::Spawn(float x, float y, float dx, int h) {
  EntitySharedPtr entity = World::AddEntityToWorld<Points>(
      [x, y, dx]() { return std::make_shared<Points>(x, y, dx); });

  entity->y_ += (h / 2) - (entity->h_ / 2);

  return entity;
}

void Points::ConfigureTexture() {
  if (!is_texture_loaded_) {
    SDLTextureSharedPtr texture =
        TextureManager::LoadTexture(entity_id_, POINTS_TEXTURE);

    texture_ = texture;

    is_texture_loaded_ = true;
  } else {
    SDLTextureSharedPtr texture = TextureManager::GetTextureById(entity_id_);

    texture_ = texture;
  }

  SDL_QueryTexture(texture_.get(), NULL, NULL, &w_, &h_);
}

void Points::ConfigureEntity() { ConfigureTexture(); }
