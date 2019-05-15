#include "Obstacle.h"
#include <QDebug>
#include <QString>
#include <QVector>
#include <cmath>
#include "CollisionDetection.h"
#include "Constants.h"
#include "soundbox.h"

int Obstacle::getSpeed() const { return speed; }

void Obstacle::toggleXMovement() {
  // qDebug("Toggle X Movement");
  this->invertXMovement *= -1;
}

void Obstacle::toggleYMovement() {
  // qDebug("Toggle Y Movement");
  this->invertYMovement *= -1;
}

Obstacle::Obstacle(int x, int y)
    : GameObject(x, y, Constants::obstacleImgFile, Constants::obstacleWidth) {
  this->speed = 0;
  this->radAngle = 0;
  this->t = 0;
  this->invertXMovement = 1;
  this->invertYMovement = -1;
}

void Obstacle::move() {
  int dx = this->speed / 10 * cos(this->radAngle) * this->invertXMovement;
  int dy = this->speed / 10 * sin(this->radAngle) * this->invertYMovement;

  this->speed = this->speed <= 0 ? 0 : this->speed - 1;
  this->x += dx / 2;
  this->y -= dy / 2;
}

void Obstacle::impulse(int boundary) {
  // removeShot must be triggered later!!!
  if (boundary == CollisionDetection::boundaryVertical) this->toggleXMovement();
  if (boundary == CollisionDetection::boundaryHorizontal)
    this->toggleYMovement();
}

void Obstacle::impulse(int speed, double radAngle) {
  // sound once the ballon is hit
  Soundbox::gotHitSound();
  qDebug("Impulse");
  this->invertXMovement = 1;
  this->invertYMovement = -1;
  this->speed = speed;
  this->radAngle = radAngle;
}
