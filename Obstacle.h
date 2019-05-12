#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "soundbox.h"
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
  Soundbox *soundbox;
};

#endif // OBSTACLE_H
