#include "defs.h"
#include "entity.h"

class Player : public Entity {
 public:
  Player(float x, float y) : Entity(x, y) {};
  int reload_frames_ = 0;

  void DoLogic() override;

  std::string GetTextureId() override;

  bool IsTextureLoaded() override;

  void SetTextureLoaded(bool is_loaded) override;

 private:
  inline static const std::string texture_id_ = PLAYER_TEXTURE_ID;

  static bool is_texture_loaded_;

  void Shoot();
};
