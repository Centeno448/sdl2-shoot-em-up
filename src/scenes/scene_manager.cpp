#include "scenes/scene_manager.h"

#include "scenes/highscore_scene.h"

void SceneManager::StaticInit() { ChangeScene(new HighscoreScene); }

SceneSharedPtr SceneManager::GetCurrentScene() { return current_scene_; }

void SceneManager::ChangeScene(Scene* new_scene) {
  current_scene_.reset(new_scene, &SceneDeleter);
  current_scene_->Init();
}

SceneSharedPtr SceneManager::current_scene_ = nullptr;
