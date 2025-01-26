#include "shootem_math.h"

#include <math.h>

#include <random>

float ShootEmMath::RandomFloat(float min, float max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(min, max);

  return static_cast<float>(dis(gen));
}

int ShootEmMath::RandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);

  return dis(gen);
}

void ShootEmMath::CalculateSlope(float x1, float y1, float x2, float y2,
                                 float &dx, float &dy) {
  float steps = std::max(std::abs(x1 - x2), std::abs(y1 - y2));

  if (steps == 0.0) {
    dx = dy = 0.0;
    return;
  }

  dx = (x1 - x2);
  dx /= steps;

  dy = (y1 - y2);
  dy /= steps;
}
