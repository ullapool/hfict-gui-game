#ifndef SHOT_H
#define SHOT_H

#include "GameObject.h"

class Shot : public GameObject
{
private:
  int speed;
  int angle;
  int rotation;
  int player;
  double t;
public:
  Shot(int x, int y, int speed, int angle, int player);
  virtual void move();
  virtual void paint(QPainter *painter);
  virtual int getSpeed();
};

#endif // SHOT_H
