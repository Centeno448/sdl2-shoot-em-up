#pragma once

class ShootEmMath {
 public:
  static float RandomNumber(float min, float max);
  static void CalculateSlope(int x1, int y1, int x2, int y2, float& dx,
                             float& dy);
};
