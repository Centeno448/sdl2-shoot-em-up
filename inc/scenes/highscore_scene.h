#pragma once

#include "defs.h"
#include "scenes/scene.h"

class HighscoreScene : public Scene {
 public:
  void DoLogic() override;
  void Draw() override;
  void Init() override;

 private:
  int scores_[MAX_HIGHSCORES] = {-1};
};
