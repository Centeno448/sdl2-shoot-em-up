#include "world.h"

#include "algorithm"
#include "collision_manager.h"
#include "enemy.h"
#include "player.h"
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

  TimerManager::RegisterTimerCallback(FPS_TARGET * 5, true, &StaticInit);
}

void World::StaticInit() {
  for (auto &e : World::entities_) {
    e->health_ = 0;
  }

  for (auto &t : CollisionManager::layers_) {
    t.second.clear();
  }

  TimerManager::RegisterTimerCallback(0, true, &Player::RegisterPlayer);

  TimerManager::RegisterTimerCallback(60, false, &Enemy::RegisterEnemy);
}
