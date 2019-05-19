#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

enum class BoundaryCollision;

class Obstacle : public GameObject
{
private:
  int speed;
  double radAngle;
  double t;
  int invertXMovement;
  int invertYMovement;
public:
  Obstacle(int x, int y);
  virtual void move();
  virtual void impulse(int speed, double radAngle);
  virtual void impulse(BoundaryCollision);
  virtual int getSpeed() const;
};

#endif // OBSTACLE_H
