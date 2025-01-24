#include "shootem_math.h"

#include <random>

float ShootEmMath::RandomNumber(float min, float max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(min, max);

  return static_cast<float>(dis(gen));
}
