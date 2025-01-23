#include "entity.h"

class Player : public Entity {
 public:
  Player(float x, float y) : Entity(x, y) {};
  int reload_;

  void DoLogic() override;
};
