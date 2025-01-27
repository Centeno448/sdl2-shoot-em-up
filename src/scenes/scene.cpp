#include "scenes/scene.h"

void SceneDeleter(Scene* scene) { scene->Cleanup(); }

void Scene::DoLogic() {}

void Scene::Draw() {}

void Scene::Cleanup() {}

void Scene::Init() {}
