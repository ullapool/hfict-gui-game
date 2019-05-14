#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "GameObject.h"
#include "Goal.h"
#include "Obstacle.h"
#include "GameArea.h"

class CollisionDetection
{
public:
  CollisionDetection();
  static bool checkBalloon(GameObject *object1, GameObject *object2);
  static bool checkGoal(Obstacle *balloon, Goal *goal);
  static double impactAngle(GameObject *object1, GameObject *object2);
  static bool outOfBounds(GameObject *object, GameArea *area);
};

#endif // COLLISIONDETECTION_H
