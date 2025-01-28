#include "scenes/game_scene.h"

#include "collision_manager.h"
#include "effects/effect_manager.h"
#include "hud.h"
#include "timer_manager.h"
#include "world.h"

GameScene::GameScene() {
  in_use_texture_ids_ = {PLAYER_ENTITY_ID,     BULLET_ENTITY_ID,
                         ENEMY_ENTITY_ID,      ENEMY_BULLET_ENTITY_ID,
                         EXPLOSION_TEXTURE_ID, POINTS_ENTITY_ID};
}

void GameScene::DoLogic() {
  EffectManager::UpdateEffects();

  TimerManager::ProcessTimers();

  World::UpdateWorld();
}

void GameScene::Draw() {
  EffectManager::DrawEffects();

  World::DrawWorld();

  HUD::Draw();
}

void GameScene::Init() { World::InitialState(); };

void GameScene::Cleanup() {
  CollisionManager::ClearLayers();

  World::ClearEntitiesNow();

  EffectManager::ClearEffectsAtLayer(1);

  TimerManager::ClearTimers();

  for (const auto &texture_id : in_use_texture_ids_) {
    TextureManager::UnloadTextureById(texture_id);
  }
}
