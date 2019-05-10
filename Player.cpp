#include "Player.h"
#include "Constants.h"

int Player::getShots() const
{
  return shots;
}

void Player::incrementShots()
{
  this->shots++;
}

int Player::getSpeed() const
{
  return speed;
}

void Player::setSpeed(int value)
{
  speed = value;
}

int Player::getAngle() const
{
  return angle;
}

void Player::setAngle(int value)
{
  angle = value;
}

Player::Player(int x, int y, bool playerTwo) : isPlayerTwo(playerTwo), shots(0), speed(0), angle(0) {
  QString imgPath = Constants::imgFolder;
  imgPath += this->isPlayerTwo ? Constants::player2ImgFile : Constants::player1ImgFile;
  int imgWidth = this->isPlayerTwo ? Constants::player2Width : Constants::player1Width;
  this->x = x;
  this->y = y;
  this->img = new QImage(imgPath);
  *this->img = this->img->scaledToWidth(imgWidth);
}

void Player::move() {}
