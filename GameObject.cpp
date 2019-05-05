#include "GameObject.h"
#include "Constants.h"
#include <QImage>

int GameObject::getY() const
{
  return y;
}

void GameObject::setY(int value)
{
  y = value;
}

int GameObject::width()
{
  return this->img->width();
}

int GameObject::height()
{
  return this->img->height();
}

QPoint GameObject::center()
{
  int x = this->x + this->width() / 2;
  int y = this->y + this->height() / 2;
  return QPoint(x, y);
}

int GameObject::radius()
{
  return (this->width() + this->height()) / 4;
}

GameObject::GameObject(int x, int y, QString imgFile, int width)
{
  this->x = x;
  this->y = y;
  this->img = new QImage(Constants::imgFolder + imgFile);
  *this->img = this->img->scaledToWidth(width);
}

GameObject::~GameObject()
{
  delete this->img;
}

void GameObject::paint(QPainter *painter)
{
  painter->drawImage(this->x, this->y, *this->img);
}

int GameObject::getX() const
{
  return x;
}

void GameObject::setX(int value)
{
  x = value;
}
