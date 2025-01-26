#pragma once

class ShootEmMath {
 public:
  static float RandomFloat(float min, float max);
  static void CalculateSlope(float x1, float y1, float x2, float y2, float& dx,
                             float& dy);
  static int RandomInt(int min, int max);
};
