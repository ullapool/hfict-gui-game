#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "GameObject.h"
#include "soundbox.h"

class Obstacle : public GameObject {
 private:
  int speed;
  double radAngle;
  double t;
  int invertXMovement;
  int invertYMovement;
  void toggleXMovement();
  void toggleYMovement();

 public:
  Obstacle(int x, int y);
  virtual void move();
  virtual void impulse(int boundary);
  virtual void impulse(int speed, double radAngle);
  //Soundbox *soundbox;
  int getSpeed() const;
};

#endif  // OBSTACLE_H
