#pragma once

#include <forward_list>
#include <string>

#include "scenes/scene.h"

class GameScene : public Scene {
 public:
  GameScene();
  void DoLogic() override;
  void Draw() override;
  void Cleanup() override;
  void Init() override;

 private:
  std::forward_list<std::string> in_use_texture_ids_;
};
