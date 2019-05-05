#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QImage>
#include <QPainter>
#include <QPoint>

class GameObject
{
private:
  QImage *img;

protected:
  int x;
  int y;

public:
  GameObject(int x, int y, QString imgFile, int width);
  virtual ~GameObject();
  virtual void move() = 0;
  virtual void paint(QPainter *painter);
  virtual int getX() const;
  virtual void setX(int value);
  virtual int getY() const;
  virtual void setY(int value);
  virtual int width();
  virtual int height();
  virtual QPoint center();
  virtual int radius();
};

#endif // GAMEOBJECT_H
