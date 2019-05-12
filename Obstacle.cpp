#include "Obstacle.h"
#include "soundbox.h"
#include "Constants.h"
#include <cmath>
#include <QDebug>
#include <QVector>
#include <QString>

Obstacle::Obstacle(int x, int y) : GameObject (x, y, Constants::obstacleImgFile, Constants::obstacleWidth) {
  this->speed = 0;
  this->radAngle = 0;
  this->t = 0;
}

void Obstacle::move() {

  int dx = this->speed/10 * cos(this->radAngle);
  int dy = this->speed/10 * sin(this->radAngle) * -1;

  this->speed = this->speed <= 0 ? 0 : this->speed - 1;
  this->x += dx / 2;
  this->y -= dy / 2;
}

void Obstacle::impulse(int speed, double radAngle)
{
  //sound once the ballon is hit
  this->soundbox = new Soundbox;
  soundbox->gotHitSound();
  qDebug("Impulse");
  this->speed = speed;
  this->radAngle = radAngle;
}

