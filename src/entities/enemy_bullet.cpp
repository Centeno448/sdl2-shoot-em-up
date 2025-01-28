#include "entities/enemy_bullet.h"

void EnemyBullet::DoLogic() {
  if (x_ < -w_ || x_ > SCREEN_WIDTH || y_ < -h_ || y_ > SCREEN_HEIGHT) {
    health_ = 0;
  }

  x_ += dx_;
  y_ += dy_;
}

std::string EnemyBullet::GetEntityId() { return entity_id_; }

void EnemyBullet::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == PLAYER_ENTITY_ID) {
    --health_;
  }
};

void EnemyBullet::ConfigureTexture() {
  if (!is_texture_loaded_) {
    SDLTextureSharedPtr texture =
        TextureManager::LoadTexture(entity_id_, ENEMY_BULLET_TEXTURE);

    texture_ = texture;

    is_texture_loaded_ = true;
  } else {
    SDLTextureSharedPtr texture = TextureManager::GetTextureById(entity_id_);

    texture_ = texture;
  }

  SDL_QueryTexture(texture_.get(), NULL, NULL, &w_, &h_);
}

void EnemyBullet::ConfigureEntity() { ConfigureTexture(); }
