#include "scene.h"

class SceneManager {
 public:
  static void StaticInit();
  static void ChangeScene(Scene* new_scene);

  static SceneSharedPtr GetCurrentScene();

 private:
  static SceneSharedPtr current_scene_;
};
