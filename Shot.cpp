#include "Shot.h"
#include <cmath>
#include "Constants.h"

Shot::Shot(int x, int y, int speed, int angle, int player) : GameObject (x, y, Constants::shotImgFile, Constants::shotWidth)
{
  this->speed = speed;
  this->angle = angle;
  this->rotation = 0;
  this->player = player;
  this->t = 0;
}

void Shot::move()
{
  if (this->player == 0) {
    this->rotation += 30;
  } else {
    this->rotation -= 30;
  }
  const double g = 9.81;
  double rad = 3.1415926 / 180 * this->angle;
  int dx = this->speed/3 * cos(rad) * t;
  int dy = this->speed/3 * sin(rad) * t - (g/2) * pow(t, 2);
  this->t += 0.1;
  this->x += dx / 2;
  this->y -= dy / 2;
}

int Shot::getSpeed()
{
  return this->speed;
}

void Shot::paint(QPainter *painter)
{
  qDebug("shot painter");
  painter->translate(this->x + this->img->width()/2, this->y + this->img->height()/2);
  painter->rotate(this->rotation);
  painter->translate(-this->x - this->img->width()/2, -this->y - this->img->height()/2);
  painter->drawImage(this->x, this->y, *this->img);
  painter->translate(this->x + this->img->width()/2, this->y + this->img->height()/2);
  painter->rotate(-this->rotation);
  painter->translate(-this->x - this->img->width()/2, -this->y - this->img->height()/2);
}
