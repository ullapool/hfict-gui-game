#include "Shot.h"
#include <cmath>
#include "Constants.h"

Shot::Shot(int x, int y, int speed, int angle) : GameObject (x, y, Constants::shotImgFile, Constants::shotWidth)
{
  this->speed = speed;
  this->angle = angle;
  this->t = 0;
}

void Shot::move() {
  const double g = 9.81;
  double rad = 3.1415926 / 180 * this->angle;
  int dx = this->speed/3 * cos(rad) * t;
  int dy = this->speed/3 * sin(rad) * t - (g/2) * pow(t, 2);
  this->t += 0.1;
  this->x += dx / 2;
  this->y -= dy / 2;
}

int Shot::getSpeed()
{
  return this->speed;
}
