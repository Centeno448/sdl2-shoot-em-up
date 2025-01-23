#include "defs.h"
#include "entity.h"

class Player : public Entity {
 public:
  Player(float x, float y) : Entity(x, y) {};
  int reload_;

  void DoLogic() override;

  std::string GetTextureId() override;

 private:
  inline static const std::string texture_id_ = PLAYER_TEXTURE_ID;

  void Shoot();
};
