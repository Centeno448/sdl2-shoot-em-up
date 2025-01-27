#pragma once

#include "scenes/scene.h"

class HighscoreScene : public Scene {
 public:
  void DoLogic() override;
  void Draw() override;
  void Init() override;
};
