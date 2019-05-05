#ifndef SHOT_H
#define SHOT_H

#include "GameObject.h"

class Shot : public GameObject
{
private:
  int speed;
  int angle;
  double t;
public:
  Shot(int x, int y, int speed, int angle);
  virtual void move();
  int getSpeed();
};

#endif // SHOT_H
