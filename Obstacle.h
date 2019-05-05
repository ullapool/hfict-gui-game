#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"


class Obstacle : public GameObject
{
private:
  int speed;
  double radAngle;
  double t;
public:
  Obstacle(int x, int y);
  virtual void move();
  virtual void impulse(int speed, double radAngle);
};

#endif // OBSTACLE_H
