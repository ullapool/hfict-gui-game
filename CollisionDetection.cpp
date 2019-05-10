#include "CollisionDetection.h"
#include "GameObject.h"
#include "GameArea.h"
#include <cmath>
#include <QDebug>

CollisionDetection::CollisionDetection() {}

bool CollisionDetection::check(GameObject *object1, GameObject *object2)
{
  int distX = abs(object1->center().rx() - object2->center().rx());
  int distY = abs(object1->center().ry() - object2->center().ry());
  int dist = sqrt(pow(distX, 2) + pow(distY, 2));

  bool isCollision = dist - object1->radius() - object2->radius() < 0;
  //qDebug() << "Distance: " << dist << " | Radius: " << (object1->radius() + object2->radius()) << " | Collision: " << isCollision;
  return isCollision;
}

double CollisionDetection::impactAngle(GameObject *object1, GameObject *object2)
{
  int distX = object1->center().rx() - object2->center().rx();
  int distY = object1->center().ry() - object2->center().ry();
  qDebug() << atan2(distY, distX);
  return atan2(distY, distX);
}

bool CollisionDetection::outOfBounds(GameObject *object, GameArea *area)
{
  if (object->getX() + object->width() <= 0) return true;
  if (object->getX() >= area->width()) return true;
  if (object->getY() >= area->height()) return true;
  return false;
}
