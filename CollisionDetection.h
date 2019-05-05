#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "GameObject.h"

class CollisionDetection
{
public:
  CollisionDetection();
  static bool check(GameObject *object1, GameObject *object2);
  static double impactAngle(GameObject *object1, GameObject *object2);
};

#endif // COLLISIONDETECTION_H
