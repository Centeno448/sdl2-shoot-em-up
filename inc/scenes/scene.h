#pragma once

#include <memory>

class Scene {
 public:
  virtual void DoLogic();
  virtual void Draw();
  virtual void Cleanup();
  virtual void Init();
};

void SceneDeleter(Scene* scene);

typedef std::shared_ptr<Scene> SceneSharedPtr;
