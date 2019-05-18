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
  static bool checkHit(GameObject *object1, GameObject *object2);
  static bool checkGoal(Obstacle *balloon, Goal *goal);
  static int checkBoundary(Obstacle *balloon, GameArea *area);
  static double impactAngle(GameObject *object1, GameObject *object2);
  static bool outOfBounds(GameObject *object, GameArea *area);

  // Boundary collision types
  static int boundaryHorizontal;
  static int boundaryVertical;
  static int boundaryNone;
};

#endif // COLLISIONDETECTION_H
