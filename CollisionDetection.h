#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "GameObject.h"
#include "GameArea.h"

class CollisionDetection
{
public:
  CollisionDetection();
  static bool check(GameObject *object1, GameObject *object2);
  static double impactAngle(GameObject *object1, GameObject *object2);
  static bool outOfBounds(GameObject *object, GameArea *area);
};

#endif // COLLISIONDETECTION_H
