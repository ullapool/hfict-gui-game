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
  int imgWidth = this->goalTwo ? Constants::goal2Width : Constants::goal1Width;
  this->x = x;
  this->y = y;
  this->img = new QImage(imgPath);
  *this->img = this->img->scaledToWidth(imgWidth);
}

Goal::~Goal() {
  delete this->img;
}

void Goal::move() {}
