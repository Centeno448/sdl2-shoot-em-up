#include "scenes/highscore_scene.h"

#include <fmt/format.h>

#include <fstream>
#include <iostream>

#include "effects/effect_manager.h"
#include "hud.h"
#include "input_manager.h"
#include "scenes/game_scene.h"
#include "scenes/scene_manager.h"

void HighscoreScene::Init() {
  std::ifstream file(HIGHSCORE_FILE, std::fstream::in);

  if (file.is_open()) {
    int score = 0, i = 0;

    while (file >> score && i < MAX_HIGHSCORES) {
      scores_[i] = score;
      ++i;
    }
  }
}

void HighscoreScene::DoLogic() {
  EffectManager::UpdateEffects();

  if (InputManager::IsKeyPressed(SDL_SCANCODE_SPACE)) {
    InputManager::SetKeyPressed(SDL_SCANCODE_SPACE, false);
    SceneManager::ChangeScene(new GameScene());
  }
}

void HighscoreScene::Draw() {
  EffectManager::DrawEffects();

  HUD::DrawText(425, 70, 255, 255, 255, "HIGHSCORES");

  int y = 150;
  for (int i = 0; i < MAX_HIGHSCORES; i++) {
    if (scores_[i] < 0) {
      HUD::DrawText(425, y, 255, 255, 255,
                    fmt::format("#{} ............. {}", (i + 1), "N/A"));
    } else {
      HUD::DrawText(425, y, 255, 255, 255,
                    fmt::format("#{} ............. {}", (i + 1), scores_[i]));
    }

    y += 50;
  }

  HUD::DrawText(425, 600, 255, 255, 255, "PRESS FIRE TO PLAY!");
}
