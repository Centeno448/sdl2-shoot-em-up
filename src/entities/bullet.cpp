#include "entities/bullet.h"

void Bullet::DoLogic() {
  if (x_ > SCREEN_WIDTH) {
    health_ = 0;
  }

  x_ += dx_;
}

std::string Bullet::GetEntityId() { return entity_id_; }

void Bullet::HandleCollision(EntitySharedPtr collided_with) {
  if (collided_with->GetEntityId() == ENEMY_ENTITY_ID) {
    --health_;
  }
};

void Bullet::ConfigureTexture() {
  if (!is_texture_loaded_) {
    SDLTextureSharedPtr texture =
        TextureManager::LoadTexture(entity_id_, BULLET_TEXTURE);

    texture_ = texture;

    is_texture_loaded_ = true;
  } else {
    SDLTextureSharedPtr texture = TextureManager::GetTextureById(entity_id_);

    texture_ = texture;
  }

  SDL_QueryTexture(texture_.get(), NULL, NULL, &w_, &h_);
}

void Bullet::ConfigureEntity() { ConfigureTexture(); }
