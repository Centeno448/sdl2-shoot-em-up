#include "world.h"

#include "algorithm"
#include "collision_manager.h"
#include "entities/enemy.h"
#include "entities/player.h"
#include "timer_manager.h"

std::forward_list<EntitySharedPtr> World::entities_ = {};

EntitySharedPtr World::GetEntityById(std::string id) {
  auto found =
      std::find_if(entities_.cbegin(), entities_.cend(),
                   [id](EntitySharedPtr e) { return e->GetEntityId() == id; });

  if (found != entities_.cend()) {
    return *found;
  }

  return nullptr;
}

void World::ResetWorld() {
  TimerManager::ClearTimers();

  TimerManager::RegisterTimerCallback(FPS_TARGET * 5, true, &InitialState);
}

void World::StaticInit(SDLRendererSharedPtr renderer) { renderer_ = renderer; }

void World::InitialState() {
  for (auto &e : World::entities_) {
    e->health_ = 0;
  }

  for (auto &t : CollisionManager::layers_) {
    t.second.clear();
  }

  TimerManager::RegisterTimerCallback(0, true, &Player::RegisterPlayer);

  TimerManager::RegisterTimerCallback(60, false, &Enemy::RegisterEnemy);
}

void World::UpdateWorld() {
  auto current_entity = entities_.begin();
  while (current_entity != entities_.end()) {
    if ((*current_entity)->IsDead()) {
      (*current_entity)->OnDeath();
      EntitySharedPtr to_delete = (*current_entity);
      ++current_entity;
      entities_.remove(to_delete);
      std::string collision_layer = to_delete->GetCollisionLayer();
      if (collision_layer.size()) {
        CollisionManager::layers_.at(collision_layer).remove(to_delete);
      }
    } else {
      (*current_entity)->DoLogic();
      CollisionManager::CheckCollision(*current_entity);
      ++current_entity;
    }
  }
}

void World::DrawWorld() {
  for (EntitySharedPtr e : entities_) {
    e->Draw(GetRenderer());
  }
}

SDL_Renderer *const World::GetRenderer() { return renderer_.get(); }
