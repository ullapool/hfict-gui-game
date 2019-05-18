#include "CollisionDetection.h"
#include "GameObject.h"
#include "Goal.h"
#include "Obstacle.h"
#include "GameArea.h"
#include <cmath>
#include <QDebug>

CollisionDetection::CollisionDetection() {}

bool CollisionDetection::checkBalloon(GameObject *object1, GameObject *object2)
{
  //qDebug("Collision Check Balloon");
  int distX = abs(object1->center().rx() - object2->center().rx());
  int distY = abs(object1->center().ry() - object2->center().ry());
  int dist = sqrt(pow(distX, 2) + pow(distY, 2));

  bool isCollision = dist - object1->radius() - object2->radius() < 0;
  //qDebug() << "Distance: " << dist << " | Radius: " << (object1->radius() + object2->radius()) << " | Collision: " << isCollision;
  return isCollision;
}

bool CollisionDetection::checkGoal(Obstacle *balloon, Goal *goal)
{
  //qDebug("Collision Check Goal");
  if (balloon->getSpeed() <= 0) return false;
  int goalInnerRadius = goal->height() / 2 - 20;
  int goalTop = goal->center().ry() - goalInnerRadius;
  int goalBottom = goal->center().ry() + goalInnerRadius;
  bool hitY = balloon->center().ry() - balloon->radius() > goalTop &&
              balloon->center().ry() + balloon->radius() < goalBottom;
  bool hitX = goal->isGoalTwo() ?
                balloon->center().rx() > goal->center().rx() :
                balloon->center().rx() < goal->center().rx();

  return hitY && hitX;
}

BoundaryCollision CollisionDetection::checkBoundary(Obstacle *balloon, GameArea *area)
{
  if (balloon->getSpeed() <= 0) return BoundaryCollision::None;
  if (balloon->center().y() <= 0) return BoundaryCollision::Top;
  if (balloon->center().y() >= 480) return BoundaryCollision::Bottom;
  if (balloon->center().x() <= 0) return BoundaryCollision::Left;
  if (balloon->center().x() >= area->width()) return BoundaryCollision::Right;
  return BoundaryCollision::None;
}

double CollisionDetection::impactAngle(GameObject *object1, GameObject *object2)
{
  //qDebug("Collision Angle");
  int distX = object1->center().rx() - object2->center().rx();
  int distY = object1->center().ry() - object2->center().ry();
  return atan2(distY, distX);
}

bool CollisionDetection::outOfBounds(GameObject *object, GameArea *area)
{
  //qDebug("Collision Out of Bounds");
  if (object->getX() + object->width() <= 0) return true;
  if (object->getX() >= area->width()) return true;
  if (object->getY() >= area->height()) return true;
  return false;
}
