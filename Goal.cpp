#include "Goal.h"
#include "Constants.h"

bool Goal::isGoalTwo() const
{
  return goalTwo;
}

Goal::Goal(int x, int y, bool goalTwo) : goalTwo(goalTwo)
{
  QString imgPath = Constants::imgFolder;
  imgPath += this->goalTwo ? Constants::goal2ImgFile : Constants::goal1ImgFile;
  this->x = x;
  this->y = y;
  this->img = new QImage(imgPath);
  *this->img = this->img->scaledToWidth(60);
}

void Goal::move() {}
