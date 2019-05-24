#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "GameObject.h"
#include "Goal.h"
#include "Obstacle.h"
#include "GameArea.h"

enum class BoundaryCollision
{
  None,
  Left,
  Right,
  Top,
  Bottom
};

class CollisionDetection
{
public:
  CollisionDetection();
  static bool checkHit(GameObject *object1, GameObject *object2);
  static bool checkGoal(Obstacle *balloon, Goal *goal);
  static BoundaryCollision checkBoundary(Obstacle *balloon, GameArea *area);
  static double impactAngle(GameObject *object1, GameObject *object2);
  static bool outOfBounds(GameObject *object, GameArea *area);
};

#endif // COLLISIONDETECTION_H
