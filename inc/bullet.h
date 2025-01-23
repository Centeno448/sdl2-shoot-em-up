#include "defs.h"
#include "entity.h"

class Bullet : public Entity {
 public:
  Bullet(float x, float y) : Entity(x, y) { dx_ = PLAYER_BULLET_SPEED; };

  void DoLogic() override;

  std::string GetTextureId() override;

 private:
  inline static const std::string texture_id_ = BULLET_TEXTURE_ID;
};
