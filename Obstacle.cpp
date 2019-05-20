#include "Obstacle.h"
#include <QDebug>
#include <QString>
#include <QVector>
#include <cmath>
#include "CollisionDetection.h"
#include "Constants.h"
#include "soundbox.h"

int Obstacle::getSpeed() const { return speed; }

Obstacle::Obstacle(int x, int y) : GameObject (x, y, Constants::obstacleImgFile, Constants::obstacleWidth)
{
  this->speed = 0;
  this->radAngle = 0;
  this->t = 0;
  this->invertXMovement = 1;
  this->invertYMovement = -1;
}

void Obstacle::move()
{
  if (this->speed == 0) return; // cancel calculation if speed is 0
  int dx = static_cast<int>(this->speed/3 * cos(this->radAngle) * this->invertXMovement);
  int dy = static_cast<int>(this->speed/3 * sin(this->radAngle) * this->invertYMovement);

  this->speed--;
  this->x += dx / 2;
  this->y -= dy / 2;
}

void Obstacle::impulse(BoundaryCollision boundary)
{
   // adding / removing 5px is a quick & dirty workaround preventing ballon from getting stuck at boundary
  switch (boundary) {
    case BoundaryCollision::None : break;
    case BoundaryCollision::Top :
      this->y += 5;
      this->invertYMovement *= -1;
      break;
    case BoundaryCollision::Bottom :
      this->y -= 5;
      this->invertYMovement *= -1;
      break;
    case BoundaryCollision::Left :
      this->x += 5;
      this->invertXMovement *= -1;
      break;
    case BoundaryCollision::Right :
      this->x -= 5;
      this->invertXMovement *= -1;
      break;
  }
}

void Obstacle::impulse(int speed, double radAngle)
{
  qDebug("Impulse");
  this->invertXMovement = 1;
  this->invertYMovement = -1;
  this->speed = speed;
  this->radAngle = radAngle;
}
